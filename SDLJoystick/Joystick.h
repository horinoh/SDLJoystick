#pragma once

#include <iostream>
#include <vector>
#include <cassert>
#define SAFE_FCLOSE(x) if(nullptr != x) { fclose(x); x = nullptr; }

#include <SDL.h>

class Joystick
{
public:
	Joystick(SDL_Joystick* js);
	virtual ~Joystick();

	void PrintCharacteristic() const;
	void PrintHapticCharacteristic() const;
	
	virtual void CreateEffect();
	virtual void PlayEffect(const int effectID);

	virtual void Update();

	static void CreateConsole();
	static void DestroyConsole();

protected:
	SDL_Joystick * joystick = nullptr;
	SDL_Haptic* haptic = nullptr;
	std::vector<int> effectIDs;

private:
	static FILE * StdOut;
	static FILE* StdErr;
};