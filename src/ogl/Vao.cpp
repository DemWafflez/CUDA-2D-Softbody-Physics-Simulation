#include "Vao.h"

Vao::Vao(int size, int count) : Vao(Utility::getSizes(size, count)) {
}

Vao::Vao(vector<int> s) : sizes(s), vbos(s.size()), buffer(init()) {
}

Vao::~Vao() {
	glDeleteBuffers(vbos.size(), vbos.data());
	glDeleteVertexArrays(1, &ptr);
}

CudaGLBuffer Vao::init() {
	CudaGLBuffer buffer(sizes);
	vbos = buffer.vbos;

	glCreateVertexArrays(1, &ptr);
	return buffer;
}

void Vao::bind() {
	glBindVertexArray(ptr);
}

void Vao::bindVbo(int i) {
	glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);
}

void Vao::initAttribs() {
	bind();

	// setup in subclass
}

void Vao::setAttrib(int i, int floats, int divisor) {
	bindVbo(i);

	glVertexAttribPointer(i, floats, GL_FLOAT, false, 0, nullptr);
	glVertexAttribDivisor(i, divisor);
	glEnableVertexAttribArray(i);
}

float* Vao::getPtr(int i) {
	return (float*) buffer.hBuffers[i];
}

void Vao::copyCuda(int i, float* src, int start, int end) {
	CudaUtility::fcopy(getPtr(i), src, start, end);
}

void Vao::writeData() {}