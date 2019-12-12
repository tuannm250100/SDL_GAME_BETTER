#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_

#include "CommonFunction.h"
#include "BaseObject.h"
#include "AmoObject.h"
#include <vector>

#define WIDTH_THREAT 80
#define HEIGHT_THREAT 33
class ThreatObject : public BaseObject
{
public:
	ThreatObject();
	~ThreatObject();

	void HandleInputAction(SDL_Event events);
	void HandleMove(const int& x_border, const int& y_border);

	void set_x_val(const int& val) { x_val_ = val; }
	void set_y_val(const int& val) { y_val_ = val; }
	int get_x_val() const { return x_val_; }
	int get_y_val() const { return y_val_; }

	void InitAmo(AmoObject* amo);
	void MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit);
	std::vector<AmoObject*> GetAmoList() const { return p_amo_list_; }
	void Reset(const int& xboder);
	void ResetAmo(AmoObject* amo);
private:
	int x_val_;
	int y_val_;

	std::vector<AmoObject*> p_amo_list_;
};
#endif // !THREATS_OBJECT_H_
