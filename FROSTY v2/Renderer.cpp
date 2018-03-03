#include "Renderer.h"

// Allow us to directly call the ImGui WndProc function.
extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

// The original WndProc function.
WNDPROC game_wndproc = nullptr;

// Hooked WndProc function to process all incoming input messages.
LRESULT __stdcall hkWndProc(HWND window, UINT message_type, WPARAM w_param, LPARAM l_param) {
	switch (message_type) {
	case WM_LBUTTONDOWN:
		G::PressedKeys[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		G::PressedKeys[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		G::PressedKeys[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		G::PressedKeys[VK_RBUTTON] = false;
		break;
	case WM_MBUTTONDOWN:
		G::PressedKeys[VK_MBUTTON] = true;
		break;
	case WM_MBUTTONUP:
		G::PressedKeys[VK_MBUTTON] = false;
		break;
	case WM_XBUTTONDOWN:
	{
		UINT button = GET_XBUTTON_WPARAM(w_param);
		if (button == XBUTTON1)
		{
			G::PressedKeys[VK_XBUTTON1] = true;
		}
		else if (button == XBUTTON2)
		{
			G::PressedKeys[VK_XBUTTON2] = true;
		}
		break;
	}
	case WM_XBUTTONUP:
	{
		UINT button = GET_XBUTTON_WPARAM(w_param);
		if (button == XBUTTON1)
		{
			G::PressedKeys[VK_XBUTTON1] = false;
		}
		else if (button == XBUTTON2)
		{
			G::PressedKeys[VK_XBUTTON2] = false;
		}
		break;
	}
	case WM_KEYDOWN:
		G::PressedKeys[w_param] = true;
		break;
	case WM_KEYUP:
		G::PressedKeys[w_param] = false;
		break;
	default: break;
	}
	// Let the renderer decide whether we should pass this input message to the game.
	if (renderer->HandleInputMessage(message_type, w_param, l_param))
		return true;


	// The GUI is inactive so pass the input to the game.
	return CallWindowProc(game_wndproc, window, message_type, w_param, l_param);
};

Renderer::~Renderer() {
	// Restore the original WndProc function.
	SetWindowLongPtr(this->window, GWLP_WNDPROC, LONG_PTR(game_wndproc));
}

bool Renderer::IsReady() const {
	// Whether 'Initialize' has been called successfully yet.
	return this->ready;
}

bool Renderer::IsActive() const {
	// Whether the GUI is accepting input and should be drawn.
	return this->ready && this->active;
}

bool Renderer::Initialize(HWND window, IDirect3DDevice9* device) {

	this->window = window;


	game_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, LONG_PTR(hkWndProc)));


	if (ImGui_ImplDX9_Init(window, device))
		this->ready = true;

	return this->ready;
}

bool Renderer::HandleInputMessage(UINT message_type, WPARAM w_param, LPARAM l_param) {
	// Toggle the menu when INSERT is pressed.
	if (message_type == WM_KEYUP && w_param == VK_INSERT)
		this->active = !this->active;

	// When the GUI is active ImGui can handle input by itself.
	if (this->active)
		ImGui_ImplDX9_WndProcHandler(this->window, message_type, w_param, l_param);

	return this->active;
}

Renderer* renderer = new Renderer;

int gimwxvorqrvk() { int hejruqbehiouc = 3668; int mlamvsnropqu = 4482; int xdffudcphlcwy = 7633; int iubcqobjln = 2150; if (hejruqbehiouc = 7) { mlamvsnropqu = 4482; } int eruonyblshil = 2150; int gulwxovktww = 7633; int dzdklkfsvwbu = 4482; int weotfkgiqjngu = 3668; int huvhtwlwiihlc = 4482; int wpomhsmgkub = 7633; int pwuzxfegmbejlx = 4482; return wpomhsmgkub; }
int vcvlgwefbeiw() { int iqahmbfbpsr = 8452; int ayrstldecckvia = 1040; int fdgbmjnxoj = 5014; int bhbzjydhe = 9179; if (iqahmbfbpsr = 7) { ayrstldecckvia = 1040; } int jioqnoprmyihi = 9179; int bjzhyochyzap = 5014; int qkqflzcj = 1040; int lvtxdixqpcd = 8452; int svaejyoddw = 1040; int ebuqqtfffm = 5014; int yhuncfvtgxl = 1040; return ebuqqtfffm; }
int hiiohsnlnoad() { int fiffasaigcub = 6723; int xnfcgrqlvfe = 8939; int bvcpxxohwlagon = 2263; int koivnwldueoy = 3609; if (fiffasaigcub = 7) { xnfcgrqlvfe = 8939; } int izymwxjdtqcz = 3609; int mebrtbrwwlb = 2263; int yhjrzjdtnswrb = 8939; int bxhgqslwkwj = 6723; int zxualvxpcudwjg = 8939; int yzrbrhxxdua = 2263; int qvhgcytmiwqqz = 8939; return yzrbrhxxdua; }
int xoutbbpvsjvbp() { int vtsrjkxmlrpf = 4561; int cfsrebmqmowc = 6852; int scbougbulegd = 5825; int pxcttursvjvw = 9056; if (vtsrjkxmlrpf = 7) { cfsrebmqmowc = 6852; } int lnwcycunmwm = 9056; int mbhueniyrozen = 5825; int kkxfdnygbvlm = 6852; int rnnwnkayd = 4561; int asytpc = 6852; int dhamuwcpfrny = 5825; int oezejepevaqnu = 6852; return dhamuwcpfrny; }