// @file GraphicBuffer.cpp

#include "GraphicBuffer.h"
#include <iostream>

namespace Graphic
{
	/*
	* �o�b�t�@�I�u�W�F�N�g���쐬����.
	*
	* @param target �o�b�t�@�I�u�W�F�N�g�̎��.<���݂���IBO or VBO>
	* @param size	���_�f�[�^�̃T�C�Y.
	* @param data	���_�f�[�^�ւ̃|�C���^.
	* @param		�o�b�t�@�I�u�W�F�N�g�̃A�N�Z�X�^�C�v.
	*/
	void BufferObject::Init(GLenum target,GLsizeiptr size,const GLvoid* data,GLenum usage)
	{
		Destroy();
		glGenBuffers(
			1,		//GLsizei 
			&id);	//GLuint* 

		glBindBuffer(
			target,		//GLenum target, 
			id);		//GLuint buffer

		glBufferData(
			target,			//GLenum target, 
			size,			//GLsizeiptr size, 
			data,			//const GLvoid* data, 
			usage);			//GLenum usage


		//Deallocation
		glBindBuffer(
			target,		//GLenum target, 
			0);			//GLuint buffer


	}

	/*
	* BufferObject���폜.
	*
	* @note		Init��,�f�X�g���N�^���ɒ��ڌĂяo�����A
	*			���o������
	*/
	void BufferObject::Destroy()
	{
		if (id)
		{
			int i = id;
			std::cout << "BufferObject::Destroy()�폜�O��ID" << i << std::endl;

			glDeleteBuffers(
				1,			//GLsizei n, 
				&id);		//const GLuint* buffers
			id = 0;
			i = id;
			std::cout << "BufferObject::Destroy()�폜���ID" << i<<std::endl;
			
		}
	}


	/*
	* VAO���쐬����.
	*
	* @param vbo ���_�o�b�t�@�I�u�W�F�N�g��ID.
	* @param ibo �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g��ID.
	*/
	void VertexArrayObject::Init(GLuint vbo,GLuint ibo)
	{
		Destroy();
		
		glGenVertexArrays(
			1,			//GLsizei n, 
			&id);		//GLuint* arrays

		glBindVertexArray(
			id);		//GLuint array

		glBindBuffer(
			GL_ARRAY_BUFFER,	//GLenum target, 
			vbo);				//GLuint buffer

		glBindBuffer(
			GL_ELEMENT_ARRAY_BUFFER,	//GLenum target, 
			ibo);						//GLuint buffer

		glBindVertexArray(
			0);			//GLuint array

	}

	/*
	* VAO�̔j��
	* 
	* @note		Init() �� �f�X�g���N�^�Ŏ����ŌĂяo����鑼
	*			���o������
	*/
	void VertexArrayObject::Destroy()
	{
		if (id)
		{
			glDeleteVertexArrays(
				1,			//GLsizei n, 
				&id);		//const GLuint* arrays
			id = 0;
		}
	}

	/**
	* ���_�A�g���r���[�g��ݒ肷��.
	*
	* @param index      ���_�A�g���r���[�g�̃C���f�b�N�X.
	* @param size       ���_�A�g���r���[�g�̗v�f��.
	* @param type       ���_�A�g���r���[�g�̌^.
	* @param normalized GL_TRUE=�v�f�𐳋K������. GL_FALSE=���K�����Ȃ�.
	* @param stride     ���̒��_�f�[�^�܂ł̃o�C�g��.
	* @param offset     ���_�f�[�^�擪����̃o�C�g�I�t�Z�b�g.
	*/
	void VertexArrayObject::VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, size_t offset)
	{
		Bind();
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(
			index,								//GLuint index, 
			size,								//GLint size, 
			type,								//GLenum type, 
			normalized,							//GLboolean normalized, 
			stride,								//GLsizei stride, 
			reinterpret_cast<GLvoid*>(offset));	//const GLvoid* pointer
		Unbind();
	}

	/*
	* VAO �������Ώۂɂ���.
	*/
	void VertexArrayObject::Bind()const
	{
		glBindVertexArray(id);		//GLuint array
	}

	/*
	* VAO �������Ώۂ���O��.
	*/
	void VertexArrayObject::Unbind()const
	{
		glBindVertexArray(0);		//GLuint array
	}

}//namespace Graphic

