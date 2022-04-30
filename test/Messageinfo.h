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

//�׻� Ŭ���̾�Ʈ�� enum ���� ��ġ�����ּ���!
enum class MessageType
{
	LogIn,
	LogOut,
	chat,

	Length,// ���� ���� �޽��� Ÿ���� �������� �� ���� ������ ������ ����!
};


class MessageInfo
{
public :
	MessageType type;
	short length;
};

class MessageInfo_LogIn : public  MessageInfo
{
public :
	int userIndex;
	string name;
public:
	MessageInfo_LogIn(char* message, int targetUser)
	{
		type = MessageType::LogIn;
		//���� �κ��� �� �� Ȯ��!
		//byteConvertor.character[0] = message[2];
		//byteConvertor.character[1] = message[3];
		//ĳ���� �� ���� �о�ͼ� �װŸ� ���ڷ� ���!
		//length = byteConvertor.shortInteger[0];
		userIndex = targetUser;
		// �޽����� 4��°���� ������ �־��ֵ��� �սô�!
		name = &(message[4]);
	}
};