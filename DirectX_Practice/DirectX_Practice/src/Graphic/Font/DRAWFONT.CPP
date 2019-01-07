#include "DrawFont.h"
#include "../../DirectX/DirectX11.h"
#include "../../util/math/Vector2.h"
#include "../../util/math/Vector3.h"
#include "../../Shader/ShaderManager.h"
#include <stdarg.h>

DrawFont::DrawFont() :
	m_DebugFont(),
	m_Effect(VERTEX_SHADER_ID::TEXTURE_SHADER, PIXEL_SHADER_ID::TEXTURE_SHADER)
{
	//m_DebugFont.Create("Ricty Diminished", 12);
	m_DebugFont.Create("APJapanesefontF", 12);
}

DrawFont::~DrawFont()
{
}

void DrawFont::Load(const std::string & fileName, int fontSize)
{
}

void DrawFont::Draw(Vector2 position, const std::string& text)
{
	m_Effect.Begin();

	// �u�����h
	DirectX11::GetInstance()->SetAlphaBlend(true, false);
	m_DebugFont.Draw(position, text);
	DirectX11::GetInstance()->SetAlphaBlend(false, false);

	m_Effect.End();
}

std::string DrawFont::format(const char * format, ...)
throw(const char *)
{
	va_list v;				// �ϒ������^
	int num = 0;			// �o�C�g��
	int res = 0;			// �Ԃ�l
	std::string ret;		// �Ԃ�l

	va_start(v, format);	// �ϒ���������J�n

	num = _vscprintf(format, v) + 1;				// �����W�J��̃o�C�g���擾
	char* buf = new char[num];						// �o�b�t�@�������A���P�[�V����

	res = _vsnprintf_s(buf, num, num, format, v);	// �o�b�t�@�ɏ����W�J��̕������ݒ�
	if (res < 0)
	{
		va_end(v);				// �ϒ���������I��
		delete[] buf;			// �o�b�t�@���
		throw "_vsnprintf_s error";
	}

	ret = buf;				// string�ɕϊ�

	va_end(v);				// �ϒ���������I��
	delete[] buf;			// �o�b�t�@���

	return ret;
}