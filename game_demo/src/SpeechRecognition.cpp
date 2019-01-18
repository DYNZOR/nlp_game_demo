//#include "SpeechRecognition.h"
//#include <iostream>
//
//SpeechRecognition* SpeechRecognition::pRecoInstance;
//
//SpeechRecognition::SpeechRecognition()
//{
//	// Initialize COM library
//	if (FAILED(::CoInitialize(nullptr))) {
//		//return EXIT_FAILURE;
//	}
//
//	std::cout << "Starting Windows Spoeech Recognition..." << std::endl;
//
//
//	ISpRecognizer* recognizer;
//
//	hr = CoCreateInstance(CLSID_SpSharedRecognizer,
//		nullptr, CLSCTX_ALL, IID_ISpRecognizer,
//		reinterpret_cast<void**>(&recognizer));
//	check_result(hr);
//
//	// Create a new reco context using the recogniser. 
//
//	hr = recognizer->CreateRecoContext(&recoContext);
//	check_result(hr);
//
//	// Disable context
//	hr = recoContext->Pause(0);
//	check_result(hr);
//
//	recoGrammar = init_grammar(recoContext);
//
//	hr = recoContext->SetNotifyWin32Event();
//	check_result(hr);
//
//	handleEvent = recoContext->GetNotifyEventHandle();
//	if (handleEvent == INVALID_HANDLE_VALUE) {
//		check_result(E_FAIL);
//	}
//
//	ULONGLONG interest;
//	interest = SPFEI(SPEI_RECOGNITION);
//	hr = recoContext->SetInterest(interest, interest);
//	check_result(hr);
//
//	//// Activate Grammar
//	hr = recoGrammar->SetDictationState(SPRS_ACTIVE);
//	check_result(hr);
//}
//
//SpeechRecognition::~SpeechRecognition()
//{
//
//}
//
//
//void SpeechRecognition::start_listening(const std::string& word) // test function 
//{
//
//	// CUT BEFORE THIS POINT 
//
//	//// Activate Grammar
//	//hr = recoGrammar->SetRuleState(ruleName1, 0, SPRS_ACTIVE);
//	//check_result(hr);
//
//	// Enable context
//	hr = recoContext->Resume(0);
//	check_result(hr);
//
//	// Wait for reco
//	HANDLE handles[1];
//	handles[0] = handleEvent;
//	WaitForMultipleObjects(1, handles, FALSE, INFINITE);
//	get_text(recoContext);
//
//
//	recoGrammar->Release();
//	::CoUninitialize();
//
//	//system("PAUSE");
//
//	//return EXIT_SUCCESS;
//}
//
//ISpRecoGrammar* SpeechRecognition::init_grammar(ISpRecoContext* recoContext)
//{
//	HRESULT hr;
//	SPSTATEHANDLE sate;
//
//	ISpRecoGrammar* recoGrammar;
//	hr = recoContext->CreateGrammar(grammarId, &recoGrammar);
//	check_result(hr);
//
//	WORD langId = GetUserDefaultUILanguage();
//	hr = recoGrammar->ResetGrammar(langId);
//	check_result(hr);
//	// TODO: Catch error and use default langId => GetUserDefaultUILanguage()
//
//	hr = recoGrammar->LoadDictation(NULL, SPLO_STATIC);
//	check_result(hr);
//
//	//// Create rules
//	//hr = recoGrammar->GetRule(ruleName1, 0, SPRAF_TopLevel | SPRAF_Active, true, &sate);
//	//check_result(hr);
//
//	// Add a word
//	//const std::wstring commandWstr = std::wstring(command.begin(), command.end());
//	//hr = recoGrammar->AddWordTransition(sate, NULL, commandWstr.c_str(), L" ", SPWT_LEXICAL, 1, nullptr);
//	//check_result(hr);
//
//	// Commit changes
//	//hr = recoGrammar->Commit(0);
//	//check_result(hr);
//
//	return recoGrammar;
//}
//
//void SpeechRecognition::get_text(ISpRecoContext* reco_context)
//{
//
//}
//
//void SpeechRecognition::check_result(const HRESULT& result)
//{
//
//}
//
