
enum class MessageType
{
	LogIn,
	LogOut,
	chat,

	Length,// ���� ���� �޽��� Ÿ���� �������� �� ���� ������ ������ ����!
};






class MessageInfo
{
	MessageType type;
	int length;
};

void SendMessage(char* massage, int length, int sendFD)
{
	// ������ ���� ���� �� "���� �ִ� ��"���� �׷��� wirte��� �θ���
	// ���� ������ Read�ϰ���?
	write(sendFD, massage, length);
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
			SendMessage(massage, length, pollFDArray[i].fd);
			
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
	case MessageType::LogIn:
		result = new MessageInfo_LogIn(input, userIndex);
		break;
	default:
		result = new MessageInfo();
		result->type = MessageType::chat; // Ÿ�� �����ֱ�
		break;
	}
	result->length =  byteConvertor.shortInteger[1] +4; // ���̸� �ݽô�!

	return result;
}

int translateMessage(int formFD, char* message, int messageLength ,MessageInfo* info)
{
	//��ü ���̿� �޽��� ���� �� �߿� ���� ������!
	int currentLength = min(messageLength, info->length);
	
	//�޸� �߿��� ���� ó���ؾ��ϴ� �޸𸮱�����!
	char* target = new char[currentLength];

	memcpy(target, message, currentLength);
	
	// Ÿ�Կ� ���� �ٸ��ൿ
	switch (info->type)
	{
	case MessageType::chat:
		BroadCastMessage(target, currentLength, formFD);
		cout << "Message Send To" << send << "User : " << target +4<< endl;
		break;
	case MessageType::LogIn:
		MessageInfo_LogIn* loginInfo = (MessageInfo_LogIn*)info;
		if(userArray[formFD]->SetLogIn(loginInfo->name));
		{
			BroadCastMessage(target, currentLength, formFD);
		};
		break;
	case MessageType::LogOut:
		break;
	default:
		break;
	}

	//��� �޽������� ���� �ϳ��� ������ ���� ȿ���� �������ϴ�.
	// ���� �� ���� �� �������� ���� ������ �� �����ϴ�.
	// ��Ƶξ��ٰ� ������ ����!
	// ��ü �޽��� ���� - ���� Ȯ���� �޽��� ����
	// ���� �ڿ� �޽����� �� �־��! ��� �ϴ� �� Ȯ���� �� ����!
	// �׷��� ó���� ���̸� ���⼭ Ȯ���ϰ� ���Կ�!
	return currentLength;
}
