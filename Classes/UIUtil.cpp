#include "UIUtil.h"

Size UIUtil::getAdaptiveSize(Size origin, Size canvaSize)
{
	Size result;
	float rateOrigin = origin.width / origin.height;
	float rateCanva = canvaSize.width / canvaSize.height;
	if (rateOrigin > rateCanva)
	{
		result.width = canvaSize.width;
		result.height = origin.height * canvaSize.width / origin.width;
	}
	else
	{
		result.height = canvaSize.height;
		result.width = origin.width * canvaSize.height / origin.height;
	}
	return result;
}
