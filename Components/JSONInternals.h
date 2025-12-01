import <string>

class JSONParser {
public:
	bool ParseJson(const char* FilePath);
};

class JSONVerifier {
public:
	bool VerifyStruct() : IsValid(False) {};
private:
	bool IsValid;
};

class ConfigMapper {
public:
	void SetAPIName();
	void SetAPIStruct();
private:
	const char* APIName;
	struct APIStruct {

	};
};