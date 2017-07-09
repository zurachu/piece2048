#include "PrecisionTimer.h"

/** @file
	�����x�^�C�}�[�֘A�̎���.
	@author zurachu
*/

#include <piece.h>

void PrecisionTimer_Construct( PrecisionTimer* p )
{
	p->count = pceTimerGetPrecisionCount();
}

unsigned long PrecisionTimer_Count( PrecisionTimer* p )
{
	unsigned long const now = pceTimerGetPrecisionCount();
	unsigned long const adjusted = pceTimerAdjustPrecisionCount( p->count, now );
	p->count = now;
	return adjusted;
}

