class User* userArray[MAX_USER_NUMBER] = { nullptr };

class User
{
	int fdNumber;
	string name = "<NULL>";

<<<<<<< HEAD
	//�̰� waitSend�� ������ ��! �� �ſ���!
	std::queue<char*> waitQueue;

	//���� ���޵��� ���� ������� �޽�����!
	char waitSend[MAX_BUFFER_SIZE] = { 0 };
	//��ٸ��� �ִ� �޽����� ����!
=======
	//�̰� waitSend�� �����Ҷ� ���
	std::queue<char*> waitQueue;

	// ���� ���޵��� ���� ������� �޽�����
	char waitSend[MAX_BUFFER_SIZE] = { 0 };
	
	//��ٸ��� �ִ� �޽����� ����
>>>>>>> 1645a97dac9399050d6e13f42756a22b645eee38
	int waitLength = 0;

	//�α����� �Ǿ��ִ°�?
	bool isLogin = false;

public:
	string GetName()
	{
		return name;
	};

	User(int targetFD)
	{
		fdNumber = targetFD;
	}

	void MessageQueue(char* message, int length)
	{
<<<<<<< HEAD
		//�޽��� �� ���̸� �Ѿ��� ��! ť���ٰ� �־��ָ� �˴ϴ�!
=======
		// �޽����� �� ���̸� �Ѿ�����! ť���ٰ� �־��ָ� �˴ϴ�!
>>>>>>> 1645a97dac9399050d6e13f42756a22b645eee38
		if (length + waitLength >= MAX_BUFFER_SIZE)
		{

		}
<<<<<<< HEAD
		else //���� �޽����� �� �� �ؿ�!
		{
			//     ����ִ� �޽��� ����     �޽���   ���̸�ŭ
			memcpy(waitSend + waitLength, message, length);

			//�� ��ŭ ���̰� �þ���ϱ�!
			waitLength += length;
		};
	}

	//�޽��� ť�� �ִ� ������ �����ϴ� �ſ���!
	void Send()
	{
		//������ �ϴ� ���̰� ���� �����ִٰ� ���� ��!
		if (waitLength > 0)
		{
			//write�¿�! �����͸� ������ ��! ���� ���̸� �ٽ� �������� �˷��ݴϴ�!
			//0���� ũ�ٰ� �Ѵٸ� �޽����� �� �������ٰ� �� �� ���� �������?
			if (write(pollFDArray[fdNumber].fd, waitSend, waitLength) > 0)
			{
				//���� ���뵵 0���� �ʱ�ȭ!
				memset(waitSend, 0, waitLength);
				//�ʱ�ȭ!
				waitLength = 0;
			};
			//if���� ���� ���ߴٴ� �Ŵ� ������ ���ߴٴ� �Ŵϱ�! �ʱ�ȭ�� ���� �ʽ��ϴ�!
=======
		else // ���� �޽����� �� �� �ؿ�!
		{
			//   ����ִ� ������ ����      �޽���      ���̸�ŭ
			memcpy(waitSend + waitLength, message, length);
			
			// �� ��ŭ ���̰� �þ���ϱ�!
			waitLength += length;
		}
	}

	// �޽��� ť�� �ִ� ������ �����ϴ� �ſ���!
	void Send()
	{
		// ������ �ϴ� ���̰� ���� ���Ҵٰ� ������
		if (waitLength > 0)
		{
			//write�¿� �����͸� ������ �� ���� ���̸� �ٽ� �������� �˷��ݴϴ�!
			// 0���� ũ�ٰ� �Ѵٸ� �޽����� �� �������ٰ� �� �� ���� �������?
			if (write(pollFDArray[fdNumber].fd, waitSend,waitLength))
			{
				// ���� ���뵵 0���� �߰�!
				memset(waitSend, 0, waitLength);
				//�ʱ�ȭ
				waitLength = 0;
			};
			//if���� ���� ���ߴٴ� �Ŵ� ������ ���ߴٴ� �Ŵϱ�! �ʱ�ȭ�� ���� �ʽ��ϴ�! 
>>>>>>> 1645a97dac9399050d6e13f42756a22b645eee38
		};
	}

	int LogIn(string wantName)
	{
		//���⿡���� ���� �ߺ� �α����̶�� �ϴ� ���� �������� �ʿ䰡 �ֽ��ϴ�!
		//���� ���� �̸��� ����� ���´ٰų� �� ����� �̹� �α��� �Ǿ��ִٰ� �� ���¿���
		//�ٽ� �α����� �õ����� �� ������ ����ٰ� �˷��� �� �ְ���!
		if (isLogin) return 2;

		//�̸� ������ �����߽��ϴ�!
		if (!SetName(wantName)) return 4;

		return 0;
	};

	//�ش� �̸��� ��ȿ���� üũ�ϱ�!
	bool CheckNameValidate(string wantName)
	{
		//�̸��� �ʹ� ��ϴ�!
		if (wantName.length() > 16) return false;

		int leftUser = currentUserNumber;
		for (int i = 0; i < MAX_USER_NUMBER; i++)
		{
			if (userArray[i] != nullptr)
			{
				//�� ���� �̸� �Ȱ��ƿ�!
				if (userArray[i]->name == wantName) return false;
				//üũ�� �༮ �ϳ� ����!
				--leftUser;
			};
		};

		return true;
	}

<<<<<<< HEAD
	bool SetName(string wantName) 
	{ 
		if (!CheckNameValidate(wantName)) return false;
		name = wantName; 
=======
	bool SetName(string wantName)
	{
		if (!CheckNameValidate(wantName)) return false;
		name = wantName;
>>>>>>> 1645a97dac9399050d6e13f42756a22b645eee38
		return true;
	};
};