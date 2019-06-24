#ifndef GPIO_MY_H_
#define GPIO_MY_H_

#include<string>
#include<fstream>
using std::string;
using std::ofstream;

#define GPIO_PATH "/sys/class/gpio/"

namespace eeroSpace {

typedef int (*CallbackType)(int);

enum GPIO_DIR{INPUT, OUTPUT};
enum GPIO_VAL{LOW = 0, HIGH = 1};
enum GPIO_EDGE{ NONE, RISING, FALLING, BOTH };

class GPIO {
private:
	int num, debounceTime;
	string name, path;

public:
	GPIO(int num);  // constructor

	//General setting functions
	virtual int setDir(GPIO_DIR);
	virtual int setVal(GPIO_VAL);

	//Advanced output
	virtual int streamOpen();
	virtual int streamWrite(GPIO_VAL);
	virtual int streamClose();
	//Advanced input
	virtual int setEdgeType(GPIO_EDGE);
	virtual int waitForEdge();
	virtual int waitForEdge(CallbackType callback); // threaded with callback

	virtual ~GPIO();  //destructor
private:
	int write(string path, string fname, int val);
	int write(string path, string fname, string val);

	bool threadRunning;
	ofstream stream;
	pthread_t thread;
	CallbackType callbackFunction;
	friend void* threadedPoll(void *value);
};

// Other functions
void* threadedPoll(void *value);

} // eeroSpace

#endif

