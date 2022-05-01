// 통합! 이라고 하는 것이죠!\
// Struct랑 비슷하게 쓰실 수 있습니다.
// 차이점이 무었이냐? 하나의 메모리를 여러가지 자료형이 공유해요!

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

//항상 클라이언트의 enum 값과 일치시켜주세요!
enum class MessageType
{
	EndOfLine, // 문자열의 끝을 판별할 때 '\0'이라고 하는 걸 파악했습니다. 메시지가 뒤에 더없다 라고 하는 걸 endofline으로 표시!
	LogIn,
	LogOut,
	chat,

	Length,// 제가 가진 메시지 타입의 개수보다 더 많은 내용 들어오면 무시!
};


class MessageInfo
{
public :
	MessageType type;
	int length;
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
		//길이 부분의 두 개 확인!
		//byteConvertor.character[0] = message[2];
		//byteConvertor.character[1] = message[3];
		//캐릭터 두 개를 읽어와서 그거를 숫자로 취급!
		//length = byteConvertor.shortInteger[0];
		userIndex = targetUser;
		// 메시지의 4번째부터 내용을 넣어주도록 합시다!
		name = &(message[4]);
	}
};