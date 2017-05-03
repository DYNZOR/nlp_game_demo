#ifndef SPEECHRECOGNITION_H
#define SPEECHRECOGNITION_H

#include <sapi53.h>
#include <string>

class SpeechRecognition
{

public:
	static SpeechRecognition* SpeechRecoInstance()
	{
		if (!pRecoInstance) {
			return pRecoInstance = new SpeechRecognition();
		}
		else {
			return pRecoInstance;
		}
	}

	void start_listening(const std::string& word); // test function 


private:
	static SpeechRecognition* pRecoInstance;

	SpeechRecognition();
	~SpeechRecognition();

	HRESULT hr;
	ISpRecoContext* recoContext;
	HANDLE handleEvent;
	ISpRecoGrammar* recoGrammar;

	const ULONGLONG grammarId = 0;
	const wchar_t* ruleName1 = L"ruleName1";

	ISpRecoGrammar* init_grammar(ISpRecoContext* recoContext);
	void get_text(ISpRecoContext* reco_context);
	void check_result(const HRESULT& result);


};

#endif