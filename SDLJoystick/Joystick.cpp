#include "stdafx.h"

#include "Joystick.h"

#pragma comment(lib, "SDL2.lib")

FILE * Joystick::StdOut = nullptr;
FILE* Joystick::StdErr = nullptr;

Joystick::Joystick(SDL_Joystick* js)
	: joystick(js)
	, haptic(SDL_HapticOpenFromJoystick(joystick))
{
	if (nullptr != haptic) {
		const auto n = SDL_HapticNumEffects(haptic);
		if (n) {
			effectIDs.reserve(n);
		}
	}
}
Joystick::~Joystick()
{
	if (nullptr != haptic) {
		if (-1 == SDL_HapticStopAll(haptic)) {
		}

		for (auto i : effectIDs) {
			SDL_HapticDestroyEffect(haptic, i);
		}
		effectIDs.clear();

		SDL_HapticClose(haptic);
	}

	if (nullptr != joystick) {
		SDL_JoystickClose(joystick);
	}
}

void Joystick::PrintCharacteristic() const
{
	if (nullptr != joystick) {
		std::cout << "---- Joysitck [" << SDL_JoystickInstanceID(joystick) << "] ----" << std::endl;

		//!< ベンダ、プロダクト、プロダクトバージョン
		std::cout << "Vendor, Product, ProductVersion = " << SDL_JoystickGetVendor(joystick) << ", " << SDL_JoystickGetProduct(joystick) << ", " << SDL_JoystickGetProductVersion(joystick) << std::endl;

		//!< 名前
		std::cout << "Name = " << SDL_JoystickName(joystick) << std::endl;

		//!< タイプ
		std::cout << "Type = ";
		switch (SDL_JoystickGetType(joystick))
		{
		default: break;
		case SDL_JOYSTICK_TYPE_UNKNOWN: std::cout << "UNKNOWN"; break;
		case SDL_JOYSTICK_TYPE_GAMECONTROLLER: std::cout << "GAMECONTROLLER"; break;
		case SDL_JOYSTICK_TYPE_WHEEL: std::cout << "WHEEL"; break;
		case SDL_JOYSTICK_TYPE_ARCADE_STICK: std::cout << "ARCADE_STICK"; break;
		case SDL_JOYSTICK_TYPE_FLIGHT_STICK: std::cout << "FLIGHT_STICK"; break;
		case SDL_JOYSTICK_TYPE_DANCE_PAD: std::cout << "DANCE_PAD"; break;
		case SDL_JOYSTICK_TYPE_GUITAR: std::cout << "GUITAR"; break;
		case SDL_JOYSTICK_TYPE_DRUM_KIT: std::cout << "DRUM_KIT"; break;
		case SDL_JOYSTICK_TYPE_ARCADE_PAD: std::cout << "ARCADE_PAD"; break;
		case SDL_JOYSTICK_TYPE_THROTTLE: std::cout << "THROTTLE"; break;
		}
		std::cout << std::endl;

		//!< GUID
		char GUID[33]; //!< 33 必要 (32文字 + NULL)
		SDL_JoystickGetGUIDString(SDL_JoystickGetGUID(joystick), GUID, sizeof(GUID));
		std::cout << "GUID = " << GUID << std::endl;

		//!< 軸 (アナログスティック)
		std::cout << "NumAxis = " << SDL_JoystickNumAxes(joystick) << std::endl;

		//!< ボタン
		std::cout << "NumButtons = " << SDL_JoystickNumButtons(joystick) << std::endl;

		//!< ハットスイッチ (十字キー)
		std::cout << "NumHats = " << SDL_JoystickNumHats(joystick) << std::endl;

		//!< トラックボール
		std::cout << "NumBalls = " << SDL_JoystickNumBalls(joystick) << std::endl;

		//!< バッテリー
		std::cout << "PowerLevel = ";
		switch (SDL_JoystickCurrentPowerLevel(joystick)) {
		default: break;
		case SDL_JOYSTICK_POWER_UNKNOWN: std::cout << "UNKNOWN"; break;
		case SDL_JOYSTICK_POWER_EMPTY: std::cout << "EMPTY"; break;
		case SDL_JOYSTICK_POWER_LOW: std::cout << "LOW"; break;
		case SDL_JOYSTICK_POWER_MEDIUM: std::cout << "MEDIUM"; break;
		case SDL_JOYSTICK_POWER_FULL: std::cout << "FULL"; break;
		case SDL_JOYSTICK_POWER_WIRED: std::cout << "WIRED"; break;
		case SDL_JOYSTICK_POWER_MAX: std::cout << "MAX"; break;
		}
		std::cout << std::endl;
	}
}

void Joystick::PrintHapticCharacteristic() const
{
	if (nullptr != haptic) {
		//!< 名前
		std::cout << "HapticName = " << SDL_HapticName(SDL_HapticIndex(haptic)) << std::endl;

		//!< デバイスが持てるエフェクト数
		std::cout << "HapticNumEffect = " << SDL_HapticNumEffects(haptic) << std::endl;
		//!< 同時に再生できるエフェクト数
		std::cout << "HapticNumEffectPlay = " << SDL_HapticNumEffectsPlaying(haptic) << std::endl;

		//!< 軸 (アナログスティック)
		std::cout << "HapticNumAxis = " << SDL_HapticNumAxes(haptic) << std::endl;

		//!< クエリ
		std::cout << "HapticQuery" << std::endl;
		std::cout << "\t";
		const auto q = SDL_HapticQuery(haptic);
		if (q & SDL_HAPTIC_CONSTANT) {
			std::cout << "CONSTANT | ";
		}

		if (q & SDL_HAPTIC_SINE) {
			std::cout << "SINE | ";
		}
		//if (q & SDL_HAPTIC_SQUARE) {
		//	std::cout << "SQUARE | ";
		//}
		if (q & SDL_HAPTIC_TRIANGLE) {
			std::cout << "TRIANGLE | ";
		}
		if (q & SDL_HAPTIC_SAWTOOTHUP) {
			std::cout << "SAWTOOTHUP | ";
		}
		if (q & SDL_HAPTIC_SAWTOOTHDOWN) {
			std::cout << "SAWTOOTHDOWN | ";
		}

		if (q & SDL_HAPTIC_LEFTRIGHT) {
			std::cout << "LEFTRIGHT | ";
		}
		if (q & SDL_HAPTIC_RAMP) {
			std::cout << "RAMP | ";
		}

		if (q & SDL_HAPTIC_SPRING) {
			std::cout << "SPRING | ";
		}
		if (q & SDL_HAPTIC_DAMPER) {
			std::cout << "DAMPER | ";
		}
		if (q & SDL_HAPTIC_INERTIA) {
			std::cout << "INERTIA | ";
		}
		if (q & SDL_HAPTIC_FRICTION) {
			std::cout << "FRICTION | ";
		}

		if (q & SDL_HAPTIC_CUSTOM) {
			std::cout << "CUSTOM | ";
		}

		if (q & SDL_HAPTIC_GAIN) {
			std::cout << "GAIN | ";
		}
		if (q & SDL_HAPTIC_AUTOCENTER) {
			std::cout << "AUTOCENTER | ";
		}
		if (q & SDL_HAPTIC_STATUS) {
			std::cout << "STATUS | ";
		}
		if (q & SDL_HAPTIC_PAUSE) {
			std::cout << "PAUSE | ";
		}
		std::cout << std::endl;
	}
}

void Joystick::CreateEffect()
{
	if (nullptr != haptic) {
		SDL_HapticEffect he;
		/**
		@ 共通項目
		length        : エフェクトの長さ(フェードイン、アウトの時間を含む)
		delay         : エフェクト開始までの遅延
		attack_length : フェードインの長さ
		attack_level  : フェードイン開始時の強さ
		fade_length   : フェードアウトの長さ
		fade_level    : フェードアウト終了時の強さ
		*/

		/**
		@ 方向
		          PC
		          N(0, -1)
				     |
		W(-1, 0)-----+----- E(1, 0)
		             |
		          S(0, 1)
		          ユーザ

		SDL_HAPTIC_POLAR
			N = 0, E = 90 * 100, S = 180 * 100, W = 270 * 100
		SDL_HAPTIC_CARTESIAN
			N = (0, -1, 0), E = (1, 0, 0), S = (0, 1, 0), W = (-1, 0, 0)
		SDL_HAPTIC_SPHERICAL
			TODO
		*/
		const SDL_HapticDirection dirPolarN = { SDL_HAPTIC_POLAR,{ 0 } };
		const SDL_HapticDirection dirPolarE = { SDL_HAPTIC_POLAR,{ 90 * 100 } };
		const SDL_HapticDirection dirPolarS = { SDL_HAPTIC_POLAR,{ 180 * 100 } };
		const SDL_HapticDirection dirPolarW = { SDL_HAPTIC_POLAR,{ 270 * 100 } };
		const SDL_HapticDirection dirCatesianN = { SDL_HAPTIC_CARTESIAN,{ 0, -1, 0 } };
		const SDL_HapticDirection dirCatesianE = { SDL_HAPTIC_CARTESIAN,{ 1,  0, 0 } };
		const SDL_HapticDirection dirCatesianS = { SDL_HAPTIC_CARTESIAN,{ 0,  1, 0 } };
		const SDL_HapticDirection dirCatesianW = { SDL_HAPTIC_CARTESIAN,{ -1,  0, 0 } };

		const auto q = SDL_HapticQuery(haptic);

#define EFFECT_CREATE_REPORT(type) std::cout << "CreateEffect [ " << effectIDs.size() - 1 << " ] " << type << std::endl;
#define CREATE_EFFECT(type) const auto effectID = SDL_HapticNewEffect(haptic, &he); if(-1 != effectID) { effectIDs.push_back(effectID); EFFECT_CREATE_REPORT(#type); }
		//!< ---- [ BEGIN ] SDL_HapticEffect,constant ----
		if (q & SDL_HAPTIC_CONSTANT) {
			memset(&he, 0, sizeof(he));
			he.type = SDL_HAPTIC_CONSTANT;
			he.constant.type = he.type;
			
			he.constant.direction = dirCatesianS;
			
			he.constant.length = 5000; //!< 長さ5秒
			he.constant.delay = 0;

			he.constant.button = 0;
			he.constant.interval = 0;

			//!< SDL_HAPTIC_CONSTANT
			he.constant.level = 20000; //!< 強さ 20000 / 32767

			he.constant.attack_length = 1000; //!< フェードイン1秒
			he.constant.attack_level = 0;
			he.constant.fade_length = 1000; //!< フェードアウト1秒
			he.constant.fade_level = 0;

			CREATE_EFFECT(SDL_HAPTIC_CONSTANT);
		}
		//!< ---- [ END ] SDL_HapticEffect,constant ----

		//!< ---- [ BEGIN ] SDL_HapticEffect.periodic ----
		if (q & SDL_HAPTIC_SINE) {
			memset(&he, 0, sizeof(he));
			he.type = SDL_HAPTIC_SINE;
			he.periodic.type = he.type;

			he.periodic.direction = dirCatesianS;

			he.periodic.length = 5000; //!< 長さ5秒
			he.periodic.delay = 0;

			he.periodic.button = 0;
			he.periodic.interval = 0;

			//!< SDL_HAPTIC_SINE
			he.periodic.period = 1000; //!< ウェーブ間隔1秒
			he.periodic.magnitude = 20000; //!< 半径 20000 / 32767
			he.periodic.offset = 0; //!< Yオフセット
			he.periodic.phase = 0; //!< Xオフセット(角度オフセット)

			he.periodic.attack_length = 1000; //!< フェードイン1秒
			he.periodic.attack_level = 0;
			he.periodic.fade_length = 1000; //!< フェードアウト1秒
			he.periodic.fade_level = 0;

			CREATE_EFFECT(SDL_HAPTIC_SINE);
		}
		//if (q & SDL_HAPTIC_SQUARE) {
		//}
		if (q & SDL_HAPTIC_TRIANGLE) {
			memset(&he, 0, sizeof(he));
			he.type = SDL_HAPTIC_TRIANGLE;
			he.periodic.type = he.type;

			//CREATE_EFFECT(SDL_HAPTIC_TRIANGLE);
		}
		if (q & SDL_HAPTIC_SAWTOOTHUP) {
			memset(&he, 0, sizeof(he));
			he.type = SDL_HAPTIC_SAWTOOTHUP;
			he.periodic.type = he.type;
			//...

			//CREATE_EFFECT(SDL_HAPTIC_SAWTOOTHUP);
		}
		if (q & SDL_HAPTIC_SAWTOOTHDOWN) {
			memset(&he, 0, sizeof(he));
			he.type = SDL_HAPTIC_SAWTOOTHDOWN;
			he.periodic.type = he.type;
			//...

			//CREATE_EFFECT(SDL_HAPTIC_SAWTOOTHDOWN);
		}
		//!< ---- [ END ] SDL_HapticEffect.periodic ----

		//!< ---- [ BEGIN ] SDL_HapticEffect.leftright ----
		if (q & SDL_HAPTIC_LEFTRIGHT) {
			//!< Xboxコントローラのような左右にモーターのあるタイプ
			memset(&he, 0, sizeof(he));
			he.type = SDL_HAPTIC_LEFTRIGHT;
			he.leftright.type = he.type;

			he.leftright.length = 5000; //!< 長さ5秒

			he.leftright.large_magnitude = 20000; //!< 強さ 20000 / 32767
			he.leftright.small_magnitude = 20000; //!< 強さ 20000 / 32767

			CREATE_EFFECT(SDL_HAPTIC_LEFTRIGHT);
		}
		//!< ---- [ END ] SDL_HapticEffect.leftright ----

		//!< ---- [ BEGIN ] SDL_HapticEffect.ramp ----
		if (q & SDL_HAPTIC_RAMP) {
			memset(&he, 0, sizeof(he));
			he.type = SDL_HAPTIC_RAMP;
			he.ramp.type = he.type;

			he.ramp.direction = dirCatesianS;

			he.ramp.length = 5000; //!< 長さ5秒
			he.ramp.delay = 0;

			he.ramp.button = 0;
			he.ramp.interval = 0;

			//!< SDL_HAPTIC_RAMP ... start から end へ線形に遷移、さらにフェードが指定されていたら加算される
			he.ramp.start = 0; //!< 開始時の強さ 0 / 32767
			he.ramp.end = 20000; //!< 終了時の強さ 20000 / 32767

			he.ramp.attack_length = 0; //!< フェードイン1秒
			he.ramp.attack_level = 0;
			he.ramp.fade_length = 0; //!< フェードアウト1秒
			he.ramp.fade_level = 0;

			CREATE_EFFECT(SDL_HAPTIC_RAMP);
		}
		//!< ---- [ END ] SDL_HapticEffect.ramp ----

		//!< ---- [ BEGIN ] SDL_HapticEffect.condition ----
		if (q & SDL_HAPTIC_SPRING) {
			memset(&he, 0, sizeof(he));
			he.type = SDL_HAPTIC_SPRING;
			he.condition.type = he.type;

			he.condition.direction = dirCatesianN; //!< 使用されないが、POLAR 以外を指定しないとエフェクト作成でコケるので指定

			he.condition.length = 0xffffffff;
			he.condition.delay = 0;

			he.condition.button = 0;
			he.condition.interval = 0;

			//!< SDL_HAPTIC_SPRING ... 軸の「位置」に基づく
			//1< 正方向の限界値
			he.condition.right_sat[0] = 0xffff; he.condition.right_sat[1] = 0xffff; he.condition.right_sat[2] = 0xffff;
			//1< 負方向の限界値
			he.condition.left_sat[0] = 0xffff; he.condition.left_sat[1] = 0xffff; he.condition.left_sat[2] = 0xffff;
			//1< 正方向の力の増加速度
			he.condition.right_coeff[0] = 2000; he.condition.right_coeff[1] = 2000; he.condition.right_coeff[2] = 2000;
			//1< 負方向の力の増加速度
			he.condition.left_coeff[0] = 2000; he.condition.left_coeff[1] = 2000; he.condition.left_coeff[2] = 2000;
			//!< デッドゾーン
			he.condition.deadband[0] = 0; he.condition.deadband[1] = 0; he.condition.deadband[2] = 0;
			//!< センター
			he.condition.center[0] = 0; he.condition.center[1] = 0; he.condition.center[2] = 0;

			CREATE_EFFECT(SDL_HAPTIC_SPRING);
		}
		if (q & SDL_HAPTIC_DAMPER) {
			memset(&he, 0, sizeof(he));
			he.type = SDL_HAPTIC_DAMPER;
			he.condition.type = he.type;
			
			he.condition.direction = dirCatesianN;

			he.condition.length = 0xffffffff;
			he.condition.delay = 0;

			he.condition.button = 0;
			he.condition.interval = 0;

			//!< SDL_HAPTIC_DAMPER ... 軸の「速度」に基づく
			he.condition.right_sat[0] = 0xffff; he.condition.right_sat[1] = 0xffff; he.condition.right_sat[2] = 0xffff;
			he.condition.left_sat[0] = 0xffff; he.condition.left_sat[1] = 0xffff; he.condition.left_sat[2] = 0xffff;
			he.condition.right_coeff[0] = 2000; he.condition.right_coeff[1] = 2000; he.condition.right_coeff[2] = 2000;
			he.condition.left_coeff[0] = 2000; he.condition.left_coeff[1] = 2000; he.condition.left_coeff[2] = 2000;
			he.condition.deadband[0] = 0; he.condition.deadband[1] = 0; he.condition.deadband[2] = 0;
			he.condition.center[0] = 0; he.condition.center[1] = 0; he.condition.center[2] = 0;

			CREATE_EFFECT(SDL_HAPTIC_DAMPER);
		}
		if (q & SDL_HAPTIC_INERTIA) {
			memset(&he, 0, sizeof(he));
			he.type = SDL_HAPTIC_INERTIA;
			he.condition.type = he.type;
			
			he.condition.direction = dirCatesianN;

			he.condition.length = 0xffffffff;
			he.condition.delay = 0;

			he.condition.button = 0;
			he.condition.interval = 0;

			//!< SDL_HAPTIC_INERTIA ... 軸の「加速度」に基づく
			he.condition.right_sat[0] = 0xffff; he.condition.right_sat[1] = 0xffff; he.condition.right_sat[2] = 0xffff;
			he.condition.left_sat[0] = 0xffff; he.condition.left_sat[1] = 0xffff; he.condition.left_sat[2] = 0xffff;
			he.condition.right_coeff[0] = 2000; he.condition.right_coeff[1] = 2000; he.condition.right_coeff[2] = 2000;
			he.condition.left_coeff[0] = 2000; he.condition.left_coeff[1] = 2000; he.condition.left_coeff[2] = 2000;
			he.condition.deadband[0] = 0; he.condition.deadband[1] = 0; he.condition.deadband[2] = 0;
			he.condition.center[0] = 0; he.condition.center[1] = 0; he.condition.center[2] = 0;

			CREATE_EFFECT(SDL_HAPTIC_INERTIA);
		}
		if (q & SDL_HAPTIC_FRICTION) {
			memset(&he, 0, sizeof(he));
			he.type = SDL_HAPTIC_FRICTION;
			he.condition.type = he.type;

			he.condition.direction = dirCatesianN;

			he.condition.length = 0xffffffff;
			he.condition.delay = 0;

			he.condition.button = 0;
			he.condition.interval = 0;

			//!< SDL_HAPTIC_FRICTION ... 軸の「移動」に基づく
			he.condition.right_sat[0] = 0xffff; he.condition.right_sat[1] = 0xffff; he.condition.right_sat[2] = 0xffff;
			he.condition.left_sat[0] = 0xffff; he.condition.left_sat[1] = 0xffff; he.condition.left_sat[2] = 0xffff;
			he.condition.right_coeff[0] = 2000; he.condition.right_coeff[1] = 2000; he.condition.right_coeff[2] = 2000;
			he.condition.left_coeff[0] = 2000; he.condition.left_coeff[1] = 2000; he.condition.left_coeff[2] = 2000;
			he.condition.deadband[0] = 0; he.condition.deadband[1] = 0; he.condition.deadband[2] = 0;
			he.condition.center[0] = 0; he.condition.center[1] = 0; he.condition.center[2] = 0;

			CREATE_EFFECT(SDL_HAPTIC_FRICTION);
		}
		//!< ---- [ END ] SDL_HapticEffect.condition ----

		//!< ---- [ BEGIN ] SDL_HapticEffect.custom ----
		if (q & SDL_HAPTIC_CUSTOM) {
			memset(&he, 0, sizeof(he));
			he.type = SDL_HAPTIC_CUSTOM;
			he.custom.type = he.type;

			he.custom.direction = dirCatesianS;
			
			he.custom.length = 5000; //!< 長さ5秒
			he.custom.delay = 0;

			he.custom.button = 0;
			he.custom.interval = 0;

			//!< SDL_HAPTIC_CUSTOM ... 形状をカスタマイズできる periodic エフェクトのように振る舞う
			he.custom.channels = 1; //!< 軸数 (最低 1)
			he.custom.period = 1000; //!< ウェーブ間隔1秒
			he.custom.samples = 10; //!< サンプル数
			std::vector<Uint16> data = {
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9
			};
			he.custom.data = data.data();

			he.custom.attack_length = 0; //!< フェードイン1秒
			he.custom.attack_level = 0;
			he.custom.fade_length = 0; //!< フェードアウト1秒
			he.custom.fade_level = 0;

			CREATE_EFFECT(SDL_HAPTIC_CUSTOM);
		}
		//!< ---- [ END ] SDL_HapticEffect.custom ----

#undef CREATE_EFFECT
#undef EFFECT_CREATED
	}

	//if (q & SDL_HAPTIC_GAIN) {
	//	if (-1 == SDL_HapticSetGain(haptic, 0-100)) { assert(true); }
	//}
	//if (q & SDL_HAPTIC_AUTOCENTER) {
	//	if (-1 == SDL_HapticSetAutocenter(haptic, 0-100)) { assert(true);}
	//}
	//if (q & SDL_HAPTIC_PAUSE) {
	//	if (-1 == SDL_HapticPause(haptic)) { assert(true); }
	//	if (-1 == SDL_HapticUnpause(haptic)) { assert(true); }
	//}
}

void Joystick::PlayEffect(const int effectID)
{
	if (nullptr != haptic && effectIDs.size() > effectID) {
		if (1 == SDL_HapticGetEffectStatus(haptic, effectID)) {
			if (-1 != SDL_HapticStopEffect(haptic, effectID)) {
				std::cout << "StopEffect" << std::endl;
			}
		}
		else {
			if (-1 != SDL_HapticRunEffect(haptic, effectID, 1)) {
				std::cout << "RunEffect" << std::endl;
			}
		}
	}
}

void Joystick::Update()
{
	if (nullptr != joystick) {
		std::cout << "---- Joystick Update ----" << std::endl;

		//!< 軸 (アナログスティック)
		for (auto i = 0; i < SDL_JoystickNumAxes(joystick); ++i) {
			const auto val = SDL_JoystickGetAxis(joystick, i);
			std::cout << SDL_JoystickName(joystick) << " Axis " << i << " = " << val << std::endl;
		}

		//!< ボタン
		for (auto i = 0; i < SDL_JoystickNumButtons(joystick); ++i) {
			const auto val = static_cast<int>(SDL_JoystickGetButton(joystick, i));
			std::cout << SDL_JoystickName(joystick) << " Button " << i << " = " << val << std::endl;
		}

		//!< ハットスイッチ (十字キー)
		for (auto i = 0; i < SDL_JoystickNumHats(joystick); ++i) {
			switch (SDL_JoystickGetHat(joystick, i))
			{
			default: break;
			case SDL_HAT_CENTERED:
				std::cout << SDL_JoystickName(joystick) << " Hat = " << "CENTERED" << std::endl;
				break;
			case SDL_HAT_UP:
				std::cout << SDL_JoystickName(joystick) << " Hat = " << "UP" << std::endl;
				break;
			case SDL_HAT_RIGHT:
				std::cout << SDL_JoystickName(joystick) << " Hat = " << "RIGHT" << std::endl;
				break;
			case SDL_HAT_DOWN:
				std::cout << SDL_JoystickName(joystick) << " Hat = " << "DOWN" << std::endl;
				break;
			case SDL_HAT_LEFT:
				std::cout << SDL_JoystickName(joystick) << " Hat = " << "LEFT" << std::endl;
				break;
			case SDL_HAT_RIGHTUP:
				std::cout << SDL_JoystickName(joystick) << " Hat = " << "RIGHTUP" << std::endl;
				break;
			case SDL_HAT_RIGHTDOWN:
				std::cout << SDL_JoystickName(joystick) << " Hat = " << "RIGHTDOWN" << std::endl;
				break;
			case SDL_HAT_LEFTUP:
				std::cout << SDL_JoystickName(joystick) << " Hat = " << "LEFTUP" << std::endl;
				break;
			case SDL_HAT_LEFTDOWN:
				std::cout << SDL_JoystickName(joystick) << " Hat = " << "LEFTDOWN" << std::endl;
				break;
			}
		}

		//!< トラックボール
		for (auto i = 0; i < SDL_JoystickNumBalls(joystick); ++i) {
			int dx, dy;
			if (0 == SDL_JoystickGetBall(joystick, i, &dx, &dy)) {
				std::cout << SDL_JoystickName(joystick) << " Ball = " << dx << ", " << dy << std::endl;
			}
		}
	}
}

void Joystick::CreateConsole()
{
	setlocale(LC_ALL, "");
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	SetConsoleTitle(TEXT("SDL"));
	freopen_s(&StdOut, "CON", "w", stdout);
	freopen_s(&StdErr, "CON", "w", stderr);
}
void Joystick::DestroyConsole()
{
	PostQuitMessage(0);
	SAFE_FCLOSE(StdOut);
	SAFE_FCLOSE(StdErr);
	FreeConsole();
}
