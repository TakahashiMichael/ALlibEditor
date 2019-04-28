// @file GraphicBuffer.cpp

#include "GraphicBuffer.h"
#include <iostream>

namespace Graphic
{
	/*
	* バッファオブジェクトを作成する.
	*
	* @param target バッファオブジェクトの種類.<現在だとIBO or VBO>
	* @param size	頂点データのサイズ.
	* @param data	頂点データへのポインタ.
	* @param		バッファオブジェクトのアクセスタイプ.
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
	* BufferObjectを削除.
	*
	* @note		Init時,デストラクタ時に直接呼び出すが、
	*			生出しも可
	*/
	void BufferObject::Destroy()
	{
		if (id)
		{
			int i = id;
			std::cout << "BufferObject::Destroy()削除前のID" << i << std::endl;

			glDeleteBuffers(
				1,			//GLsizei n, 
				&id);		//const GLuint* buffers
			id = 0;
			i = id;
			std::cout << "BufferObject::Destroy()削除後のID" << i<<std::endl;
			
		}
	}


	/*
	* VAOを作成する.
	*
	* @param vbo 頂点バッファオブジェクトのID.
	* @param ibo インデックスバッファオブジェクトのID.
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
	* VAOの破棄
	* 
	* @note		Init() と デストラクタで自動で呼び出される他
	*			生出しも可
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
	* 頂点アトリビュートを設定する.
	*
	* @param index      頂点アトリビュートのインデックス.
	* @param size       頂点アトリビュートの要素数.
	* @param type       頂点アトリビュートの型.
	* @param normalized GL_TRUE=要素を正規化する. GL_FALSE=正規化しない.
	* @param stride     次の頂点データまでのバイト数.
	* @param offset     頂点データ先頭からのバイトオフセット.
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
	* VAO を処理対象にする.
	*/
	void VertexArrayObject::Bind()const
	{
		glBindVertexArray(id);		//GLuint array
	}

	/*
	* VAO を処理対象から外す.
	*/
	void VertexArrayObject::Unbind()const
	{
		glBindVertexArray(0);		//GLuint array
	}

}//namespace Graphic

