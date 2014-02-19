#ifndef _MODEL_INSTANCE_H
#define _MODEL_INSTANCE_H

#include "ModelAsset.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ModelInstance
{
public:
	ModelInstance(ModelAsset* asset = NULL,glm::mat4 _trans = glm::mat4(1.0f)):
				_asset(asset),_trans(_trans)
	{
	
	}

	void render();

	ModelAsset* getAsset()
	{
		return _asset;
	}
	glm::mat4 getTrans()
	{
		return _trans;
	}
	void setAsset(ModelAsset* asset)
	{
		_asset = asset;
	}
	void setTrans(glm::mat4 trans)
	{
		_trans = trans;
	}
private:
	ModelAsset* _asset;
	glm::mat4 _trans;
};


#endif //_MODEL_INSTANCE_H