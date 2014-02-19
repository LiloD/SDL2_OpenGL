#include "ModelInstance.h"
void ModelInstance::render()
{
	_asset->_program->use();

	_asset->_texture->BindTexture(0);
	
	_asset->_program->SetUniform("texKitten",0);

	glBindVertexArray(_asset->_vaoId);

	glDrawArrays(GL_TRIANGLES,_asset->_drawStart,_asset->_drawCount);

}
