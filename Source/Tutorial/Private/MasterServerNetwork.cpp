// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorial.h"
#include "MasterServerNetwork.h"

FString UMasterServerNetwork::address = TEXT("127.0.0.1");
int32 UMasterServerNetwork::port = 1337;

FString StringFromBinaryArray(const TArray<uint8>& BinaryArray)
{
	//Create a string from a byte array!
	const std::string cstr(reinterpret_cast<const char*>(BinaryArray.GetData()), BinaryArray.Num());

	//FString can take in the c_str() of a std::string
	return FString(cstr.c_str());
}

void UMasterServerNetwork::requestServer(FString & outIp, int32 & outPort, bool & success)
{
	FSocket* Socket = NULL;
	if (connectToMasterServer(Socket))
	{
		json::Object message;
		message["message_type"] = "CLRS";
		message["number_of_players"] = 1; // Hard coded

		bool successful = sendMessage(Socket, message);

		if (successful)
		{
			uint32 receivedSize;
			int i = 0;
			while (!Socket->HasPendingData(receivedSize) && i < 10) // TODO: FIXME
			{
				FPlatformProcess::Sleep(0.1);
				++i;
			}
			TArray<uint8> ReceivedData;
			ReceivedData.Init(receivedSize);
			int32 Read = 0;
			Socket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);

			// TODO: Maybe check if correct values?
			FString tempMessage = StringFromBinaryArray(ReceivedData);
			std::string tempStringMessage(TCHAR_TO_UTF8(*tempMessage));
			json::Value jsonMessage = json::Deserialize(tempStringMessage);
			if (jsonMessage.GetType() == json::ObjectVal)
			{
				json::Object objectMessage = jsonMessage.ToObject();
				outIp = FString(objectMessage["server_ip"].ToString().c_str());
				outPort = objectMessage["server_port"].ToInt();
				success = true;
			}
			else
			{
				outIp = "";
				outPort = -1;
				success = false;
			}
		}
		else
			success = false;
		Socket->Close();
	}
	else
		success = false;
}

void UMasterServerNetwork::registerAsServer(int32 inPort, bool & success)
{
	FSocket* Socket = NULL;
	if (connectToMasterServer(Socket))
	{
		json::Object message;
		message["message_type"] = "NWSR";
		message["port_number"] = inPort;

		success = sendMessage(Socket, message);
		return;
	}
	success = false;
}

void UMasterServerNetwork::unregister(int32 inPort, bool & success)
{
	FSocket* Socket = NULL;
	if (connectToMasterServer(Socket))
	{
		json::Object message;
		message["message_type"] = "UNSR";
		message["port_number"] = inPort;

		success = sendMessage(Socket, message);
		return;
	}
	success = false;
}

bool UMasterServerNetwork::connectToMasterServer(FSocket* & Socket)
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);

	//	TSharedRef addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	addr->SetIp(ip.GetValue());
	addr->SetPort(port);

	return Socket->Connect(*addr);
}

bool UMasterServerNetwork::sendMessage(FSocket* Socket, json::Object & jobj)
{
	std::string serialization = json::Serialize(jobj);
	FString message(serialization.c_str());
	TCHAR *serializedChar = message.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);
	int32 sent = 0;

	return Socket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
}



