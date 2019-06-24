#ifndef PWM_H_
#define PWM_H_

#include<string>
using std::string;
#define PWM_PATH "/sys/class/pwm/"
#define PWM_PERIOD "period"
#define PWM_DUTY "duty_cycle"
#define PWM_ENABLE "enable"

namespace eeroSpace {

class PWM{

private:
	string pin, chip, channel, path, chipPath;
	unsigned int duty, period;
	virtual int write(string path, string fname, string value);
	virtual int write(string path, string filename, int value);
public:
	PWM(string pin);
	virtual int export_device();
	virtual int select_chip();
	virtual int setInitValues();
	virtual int setPeriod(unsigned int period_ns);
	virtual int setDuty(unsigned int duty_ns);
	virtual int setState(int state);
	virtual ~PWM();
};

} //eeroSpace
#endif
