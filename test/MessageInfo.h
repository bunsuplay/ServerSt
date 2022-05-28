//����! �̶�� �ϴ� ������!
//Struct�� ����ϰ� ���� �� �ֽ��ϴ�!
//�������� �����̳�? �ϳ��� �޸𸮸� �������� �ڷ����� �����ؿ�!

//[0][0][0][10]
//          10  int
//          \n  char[3]
union ConvertionBase
{
	unsigned int uInteger;
	int integer;
	float floating;
	char character[4];
	short shortInteger[2];
	unsigned short uShortInteger[2];
};
ConvertionBase byteConvertor;

//�׻� Ŭ���̾�Ʈ�� enum���� ��ġ�����ּ���!
enum class MessageType
{
	EndOfLine, //���ڿ��� ���� �Ǵ��� �� \0�̶�� �ϴ� �� �ľ��߽��ϴ�! �޽����� �ڿ� �� ���� ��� �ϴ� �� EndOfLine���� ǥ��!
	SignUp,
	LogIn,
	LogOut,
	Chat,
	Input,

	Unknown,  //���� ���� �𸣰ڴ� ����!
	Length
	//���� ���� �޽��� Ÿ���� �������� �� ���� ������ ������ ����!
};

enum class InputType
{
	Button0,
	Button1,
	Button2,
};

string SaveHashCode(string input)
{
	return sha256(input);
	
}

class MessageInfo
{
public :
	MessageType type;
	int length;
	int userIndex;
};

class MessageInfo_Login : public MessageInfo
{
public :
	string name;
	string password;
	MessageInfo_Login(char* message, int targetUser)
	{
		type = MessageType::LogIn;

		userIndex = targetUser;
		//�޽����� 4��°���� ������ �־��ֵ��� �սô�!
		name = &(message[4]);
		int currentIndex = 4;
		//0�� �� ������ �̵��ϱ�!
		while (message[currentIndex] != 0) ++currentIndex;

		//0�� �Ǵ� ���� ĭ���� password�� �Ӹ�!
		++currentIndex;
		password = &(message[currentIndex]);

		// ��й�ȣ�� �ؽ��ڵ�� ��ȯ
		password = SaveHashCode(password);
	}
};

class MessageInfo_SignUp : public MessageInfo
{
public:
	string name;
	string password;
	string nicname;
	MessageInfo_SignUp(char* message, int targetUser)
	{
		type = MessageType::SignUp;

		userIndex = targetUser;
		//�޽����� 4��°���� ������ �־��ֵ��� �սô�!
		name = &(message[4]);
		int currentIndex = 4;
		//0�� �� ������ �̵��ϱ�!
		while (message[currentIndex] != 0) ++currentIndex;

		//0�� �Ǵ� ���� ĭ���� password�� �Ӹ�!
		++currentIndex;
		password = &(message[currentIndex]);

		// ��й�ȣ�� �ؽ��ڵ�� ��ȯ
		password = SaveHashCode(password);

		//0�� �� ������ �̵��ϱ�!
		while (message[currentIndex] != 0) ++currentIndex;
		//0�� �Ǵ� ���� ĭ���� nicname���� �Ӹ�!
		++currentIndex;
		nicname = &(message[currentIndex]);
	}
};

class MessageInfo_Chat : public MessageInfo
{
public:
	string value;

	MessageInfo_Chat(char* message, int targetUser)
	{
		type = MessageType::Chat;

		userIndex = targetUser;
		//�޽����� 4��°���� ������ �־��ֵ��� �սô�!
		value = &(message[4]);
	}
};

class MessageInfo_Input : public MessageInfo
{
public:
	InputType currentType;

	MessageInfo_Input(InputType wantType, int targetUser)
	{
		type = MessageType::Input;

		currentType = wantType;
		userIndex = targetUser;
	}
};