#include <string>
#include <vector>


struct APIStruct {
	std::string name;
	std::string rename;
	std::string returnType;
	std::vector<std::string> parameters;
};

class JSONParser {
public:
	std::vector<APIStruct> ParseJson(const std::string& filePath);
};

class JSONVerifier {
public:
	bool JSONVerifier() : IsValid(false) {}
	bool VerifyStruct();
private:
	bool IsValid;
};

class ConfigMapper {
public:
	void SetAPIName(std::vector<APIStruct>& apiList) {
		apiList = APIs;
	}
	const std::vector<APIStruct>& GetAPIList() const {
		return APIs;
	}

private:
	std::vector<APIStruct> APIs;
};