#include "sample_call.h"
#include <misc/hostenv.h>

#include <iostream>



namespace Qx::mod_sample
{

void testPrint()
{
    dbg_print() << "HELLO SAMPLE MOD ...";
    dbg_print() << HostEnv::User::home();
}


}

