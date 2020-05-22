#include "Factory.h"
//#include "CommIntf.h"
#include <iostream>

using namespace std;

int main(void)
{
    CommIntf *pCommIntf;
    AER_Msg_t smsg,rmsg;

    pCommIntf = Factory::Create(MPI);

    smsg.NodeAddr = 0x12345678;
    smsg.LocalUnitAddr = 0xdeadbeef;
    smsg.payload = 7;

    pCommIntf->Send_Data(smsg);
    rmsg = pCommIntf->Recv_Data();

    cout << "Received msg is ..." << endl;
    cout << hex << "Node Address = 0x" << rmsg.NodeAddr << endl;
    cout << hex << "LocalUnit Address = 0x" << rmsg.LocalUnitAddr << endl;
    cout << "Payload = " << rmsg.payload << endl;

    if(pCommIntf) {
        delete pCommIntf;
	pCommIntf = nullptr;
    }

    return 0;
}
