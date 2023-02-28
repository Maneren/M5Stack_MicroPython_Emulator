#include "M5Stack_MicroPython.h"

#include <fstream>

#include "M5Stack/M5Stack.h"
#include "M5Stack/M5Stack_UI.h"
#include "M5Stack/UIFlow.h"
#include "M5Stack/Machine.h"
#include "M5Stack/EasyIO.h"

CM5Stack_VM::CM5Stack_VM() {
	PyImport_AppendInittab("m5stack", PyInit_m5stack);
	PyImport_AppendInittab("m5stack_ui", PyInit_m5stack_ui);
	PyImport_AppendInittab("m5ui", PyInit_m5stack_ui);
	PyImport_AppendInittab("machine", PyInit_machine);
	PyImport_AppendInittab("uiflow", PyInit_uiflow);
	PyImport_AppendInittab("easyIO", PyInit_easyIO);
	Py_Initialize();

	mMain_Module = py::import("__main__");
	mMain_Namespace = mMain_Module.attr("__dict__");
}

bool CM5Stack_VM::Load_File(const std::filesystem::path& path) {

	std::ifstream fpy(path);
	if (!fpy.is_open()) {
		return false;
	}

	mPy_File_Contents = std::string((std::istreambuf_iterator<char>(fpy)), std::istreambuf_iterator<char>());

	return true;
}

const std::string& CM5Stack_VM::Get_File_Contents() const {
	return mPy_File_Contents;
}

void CM5Stack_VM::Run() {

	if (mPy_Thread && mPy_Thread->joinable()) {
		// TODO: terminate it somehow?
		mPy_Thread->join();
	}

	mPy_Thread = std::make_unique<std::thread>(&CM5Stack_VM::Py_Thread_Fnc, this);
}

void CM5Stack_VM::Py_Thread_Fnc() {

	// TODO: solve termination somehow

	try
	{
		py::exec(mPy_File_Contents.c_str(), mMain_Namespace);
	}
	catch (const py::error_already_set&) {
		PyErr_Print();
	}
}
