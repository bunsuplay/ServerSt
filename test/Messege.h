
enum class MessageType
{
	LogIn,
	LogOut,
	chat,

	Length,// ���� ���� �޽��� Ÿ���� �������� �� ���� ������ ������ ����!
};

// ����! �̶�� �ϴ� ������!\
// Struct�� ����ϰ� ���� �� �ֽ��ϴ�.
// �������� �����̳�? �ϳ��� �޸𸮸� �������� �ڷ����� �����ؿ�!

//[0][0][0][10]
//			10 int
//			\n	char[i]
union ConvertionBase
{
	unsigned int uInteger;
	int integer;

	float floating;

	char character[4];

	short shortInteger[2];
	unsigned short ushortInteger[2];
};
ConvertionBase byteConvertor;

struct MessageInfo
{
	MessageType type;
	int length;
};
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
			// ������ ���� ���� �� "���� �ִ� ��"���� �׷��� wirte��� �θ���
			// ���� ������ Read�ϰ���?
			//    �����  ����       �޽���,     ����
			if (write(pollFDArray[i].fd, message, length))
			{
				//���´�!
				if (++send >= currentUserNumber) break;
			};

		};
	};
	cout << "Message Send To " << send << " User : " << message << endl;
}

//�޽����� �����ϴ� �뵵					���� ���� int�ּ���!
MessageInfo ProcessMessage(char input[4])
{
	for (int i = 0; i < 4; i++)
	{
		byteConvertor.character[i] = input[i];

	}
	// �޽���Ÿ��    ����
	// [][]			[][]

	MessageInfo result;

	result.type =  (MessageType)byteConvertor.shortInteger[0]; // Ÿ�Ե� �����ֱ�
	result.length =  byteConvertor.shortInteger[1] +4; // ���̸� �ְ�

	return result;
}

int translateMessage(int formFD, char* message, int messageLength ,MessageInfo info)
{
	//��ü ���̿� �޽��� ���� �� �߿� ���� ������!
	int currentLength = min(messageLength, info.length);
	
	//�޸� �߿��� ���� ó���ؾ��ϴ� �޸𸮱�����!
	char* target = new char[currentLength];

	memcpy(target, message, currentLength);
	
	// Ÿ�Կ� ���� �ٸ��ൿ
	switch (info.type)
	{
	case MessageType::chat:
		BroadCastMessage(target, currentLength, formFD);
		break;
	case MessageType::LogIn:
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
