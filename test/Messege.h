
//enum class MessageType
//{
//	LogIn,
//	LogOut,
//	chat,
//
//	Length,// ���� ���� �޽��� Ÿ���� �������� �� ���� ������ ������ ����!
//};



bool SendMessage(char* massage, int length, int sendFD)
{
	// ������ ���� ���� �� "���� �ִ� ��"���� �׷��� wirte��� �θ���
	// ���� ������ Read�ϰ���?
	write(sendFD, massage, length);
	return true;
}

//                                                 ���ο��� ������� �⺻������ true����!
//												�׷���.. üũ���ص� �ǰ���!
//												üũ�Ϸ��� FD�� �����Ǿ�� �Ǵϱ�!\
//												sendSelf�� false�� �ϰ� ������ sendFD�� 
//												�� ���ؾ� �� �̴ϴ�!
void BroadCastMessage(char* message, int length, int sendFD = -1, bool sendSelf = true)
{
	//����� ������ �ο����� �˰� �ֽ��ϴ�.
	// ������ �� ���� �ʾƵ� �������� �� ������ �ߴٸ�
	// ���� ��.. �� �� �ʿ� �ֳ�!
	// ���� ������ send�� 1�� �÷��ְ�, ��������ŭ ���´ٸ� ������!
	// sendSelf�� false�� -> �������� �����ִ� �� �ƴϸ�! ������ �ϴ� ���� ������
	// ��������� �ϰ���! �������� ������ �� Ĩ�ô�!
	// �ݺ����� �� �� �� ��µ�.. ������..? �ϸ鼭 ������ �� �ſ���! �װ� �����ֱ�!
	int send = sendSelf ? 0 : 1;
	//          ����?    ture  : false
	//        �������� ����?  0���´�! : 1�� ���³���!

	// 0���� ���� ����!  �ִ�ġ���� ���ų� ,�Ǵ�   ���� ���� ����ŭ ���´ٸ�!
	for (int i = 1; i < MAX_USER_NUMBER; i++) // || send >= currentUserNumber; i++
	{
		// �������� �� ��������! �̶�� �Ҷ� ��ƿ� ������ �ִٸ� �Ѿ��!
		if (!sendSelf && i == sendFD) continue;

		if (pollFDArray[i].fd != -1)
		{
			//          �޽���,     ����,       ����� ����
			SendMessage(message, length, pollFDArray[i].fd);
			
			//���´�!
			if (++send >= currentUserNumber) break;
			

		};
	};
}

//�޽����� �����ϴ� �뵵  	���� ���� int�ּ���!   �̰� �� ����
MessageInfo* ProcessMessage(char* input, int userIndex)
{
	for (int i = 0; i < 4; i++)
	{
		byteConvertor.character[i] = input[i];

	}
	// �޽���Ÿ��    ����
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
	result->length =  byteConvertor.shortInteger[1] +4; // ���̸� �ݽô�!

	return result;
}

int translateMessage(int formFD, char* message, int messageLength ,MessageInfo* info)
{

	// �ƹ� �͵� ���µ���?      // ������ �̵�!
	if (info == nullptr) return MAX_BUFFER_SIZE;

	//��ü ���̿� �޽��� ���� �� �߿� ���� ������!
	int currentLength = min(messageLength, info->length);
	
	//�޸� �߿��� ���� ó���ؾ��ϴ� �޸𸮱�����!
	char* target = new char[currentLength];

	//memcpy(target, message, currentLength);
	
	// Ÿ�Կ� ���� �ٸ��ൿ
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
				target[i] = 32; // �����̽���
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
		//           ������ȣ  ��������
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
		return MAX_USER_NUMBER; //�ִ�ġ���� �о �� �ڿ� �޽����� �����ٰ� �˷��ݽô�.
	default:
		break;
	}

	//�޽��� ó�� �Ϸ�!
	delete info;



	//��� �޽������� ���� �ϳ��� ������ ���� ȿ���� �������ϴ�.
	// ���� �� ���� �� �������� ���� ������ �� �����ϴ�.
	// ��Ƶξ��ٰ� ������ ����!
	// ��ü �޽��� ���� - ���� Ȯ���� �޽��� ����
	// ���� �ڿ� �޽����� �� �־��! ��� �ϴ� �� Ȯ���� �� ����!
	// �׷��� ó���� ���̸� ���⼭ Ȯ���ϰ� ���Կ�!
	return currentLength;
}
