#include "PceWaveInfo.h"

/** @file
	PCEWAVEINFO �֘A�̎���.
	@author zurachu
*/

#include <piece.h>
#include <string.h>

void PceWaveInfo_Construct( PCEWAVEINFO* p, unsigned char* source )
{
	memcpy( p, source + 8, sizeof(PCEWAVEINFO) );
	p->pData = source + 8 + sizeof(PCEWAVEINFO);
}

