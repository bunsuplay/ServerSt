
//enum class MessageType
//{
//	LogIn,
//	LogOut,
//	chat,
//
//	Length,// 제가 가진 메시지 타입의 개수보다 더 많은 내요잉 들어오면 무시!
//};



bool SendMessage(char* massage, int length, int sendFD)
{
	// 서버가 무언가 보낼 때 "적어 주는 거"에요 그래서 wirte라고 부르고
	// 받을 때에는 Read하겠죠?
	write(sendFD, massage, length);
	return true;
}

//                                                 본인에게 보내기는 기본적으로 true에요!
//												그럼뭐.. 체크안해도 되겠죠!
//												체크하려면 FD가 설정되어야 되니까!\
//												sendSelf를 false로 하고 싶으면 sendFD도 
//												꼭 정해야 할 겁니다!
void BroadCastMessage(char* message, int length, int sendFD = -1, bool sendSelf = true)
{
	//저희는 유저의 인원수를 알고 있습니다.
	// 끝까지 다 돌지 않아도 유저한테 다 전달을 했다면
	// 굳이 뭐.. 더 돌 필요 있나!
	// 보낼 때마나 send를 1씰 늘려주고, 유저수만큼 보냈다면 끝내기!
	// sendSelf가 false면 -> 본인한테 보내주는 게 아니면! 보내야 하는 유저 개수를
	// 수정해줘야 하겠죠! 본인한테 보내준 셈 칩시다!
	// 반복문이 한 명 덜 줬는데.. 누구지..? 하면서 끝까지 갈 거에요! 그거 막아주기!
	int send = sendSelf ? 0 : 1;
	//          조건?    ture  : false
	//        본인한테 보냄?  0명보냈다! : 1명 보냈놨다!

	// 0번은 리슨 소켓!  최대치까지 갔거나 ,또는   현재 유저 수만큼 보냈다면!
	for (int i = 1; i < MAX_USER_NUMBER; i++) // || send >= currentUserNumber; i++
	{
		// 본인한테 안 보낼거임! 이라고 할때 밥아온 정보가 있다면 넘어가기!
		if (!sendSelf && i == sendFD) continue;

		if (pollFDArray[i].fd != -1)
		{
			//          메시지,     길이,       대상의 소켓
			SendMessage(message, length, pollFDArray[i].fd);
			
			//보냈다!
			if (++send >= currentUserNumber) break;
			

		};
	};
}

//메시지를 구분하는 용도  	길이 받을 int주세요!   이걸 준 유저
MessageInfo* ProcessMessage(char* input, int userIndex)
{
	for (int i = 0; i < 4; i++)
	{
		byteConvertor.character[i] = input[i];

	}
	// 메시지타입    길이
	// [][]			[][]

	MessageInfo*  result;
	
	switch ((MessageType)byteConvertor.shortInteger[0])
	{
	case MessageType::EndOfLine:
		return nullptr;
	case MessageType::LogIn:     result = new MessageInfo_LogIn(input, userIndex);
		break;
	case MessageType::chat:      result = new MessageInfo_Chat(input, userIndex);
		break;
	default:                     result = new MessageInfo();
		                         result->type = MessageType::Unknown;
	}
	result->length =  byteConvertor.shortInteger[1] +4; // 길이를 줍시다!

	return result;
}

int translateMessage(int formFD, char* message, int messageLength ,MessageInfo* info)
{

	// 아무 것도 없는데요?      // 끝까지 이동!
	if (info == nullptr) return MAX_BUFFER_SIZE;

	//전체 길이와 메시지 길이 둘 중에 작은 값으로!
	int currentLength = min(messageLength, info->length);
	
	//메모리 중에서 제가 처리해야하는 메모리까지만!
	char* target = new char[currentLength];

	//memcpy(target, message, currentLength);
	
	// 타입에 따라 다른행동
	switch (info->type)
	{
	case MessageType::chat:
	{
		MessageInfo_Chat* chatInfo = (MessageInfo_Chat*)info;

		memcpy(target + 10, message +4, currentLength -20);
		byteConvertor.ushortInteger[0] = (short)MessageType::chat;
		byteConvertor.ushortInteger[1] = currentLength;

		for (int i = 0; i < 4; i++)
		{
			target[i] = byteConvertor.character[i];
		};

		string fromName = userArray[formFD]->GetName();
		for (int i = 4; i < 20; i++)
		{
			if (i > fromName.size())
			{
				target[i] = 32; // 스페이스바
			}
			else
			{
				target[i] = fromName[i - 4];
			};
		};
		target[19] = ':';

		BroadCastMessage(target, currentLength, formFD);
		cout << "Message Send To" << send << "User : " << target + 4 << endl;
		break;
	}
	case MessageType::LogIn:
	{
		MessageInfo_LogIn* loginInfo = (MessageInfo_LogIn*)info;
		
		cout << "Someone Try Login! Name is :" << loginInfo->name << "!!" << endl;
		//           유저번호  성공여부
		//[][] [][]  [][][][] []
		char sendResult[9] = { 0 };

		byteConvertor.shortInteger[0] = (short)MessageType::LogIn;
		byteConvertor.shortInteger[1] = 5;

		for (int i = 0; i < 4; i++)
		{
			sendResult[i] = byteConvertor.character[1];
		}

		if (userArray[formFD]->SetLogIn(loginInfo->name))
		{
			cout << "Login Succsed" << endl;
		}
		else
		{
			sendResult[8] = 1;
			cout << "false Succesed" << endl;
		}

		SendMessage(sendResult, 9,pollFDArray[formFD].fd);
		break;
	}
	case MessageType::LogOut:
		break;
	case MessageType::EndOfLine:
		return MAX_USER_NUMBER; //최대치까지 밀어서 그 뒤에 메시지가 더없다고 알려줍시다.
	default:
		break;
	}

	//메시지 처리 완료!
	delete info;



	//사실 메시지같은 경우는 하나씩 보내면 조금 효율이 떨어집니다.
	// 보낼 수 있을 때 여러개를 같이 보내는 게 좋습니다.
	// 모아두었다가 보내는 개념!
	// 전체 메시지 길이 - 지금 확인한 메시지 길이
	// 아직 뒤에 메시지가 더 있어요! 라고 하는 걸 확인할 수 있죠!
	// 그래서 처리한 길이를 여기서 확인하고 갈게요!
	return currentLength;
}
