#pragma once
#include <cstdint>
#include <algorithm>

#define BLOCK_SIZE 64

typedef uint8_t vect[BLOCK_SIZE];

typedef struct GOSTHashContext
{
	vect buffer; // ����� ��� ���������� ����� ����������� ���������
	vect hash; // �������� ��������� ����������
	vect h; // ������������� ��������� ����������
	vect N; //
	vect Sigma; // ����������� �����
	vect v_0; // ����������������� ������
	vect v_512; // ����������������� ������
	size_t buf_size; // ������ ���������� ����� ���������
	
	// (������� ��������� ������ ��������� 64 ����)
	int hash_size;   // ������ ���-����� (512 ��� 256 ���)
} TGOSTHashContext;



class Gost34_2012
{
public:

	Gost34_2012();
	void GOSTHashUpdate(TGOSTHashContext* ctx, const uint8_t* data, size_t len);
	void GOSTHashFinal(TGOSTHashContext* ctx);
	void GOSTHashInit(TGOSTHashContext* ctx, uint16_t hash_size);

private:
	void GOSTHashAdd512(const uint8_t* a, const uint8_t* b, uint8_t* c);
	void GOSTHashGetKey(uint8_t* k, int i);

	void GOSTHashStage_2(TGOSTHashContext* ctx, const uint8_t* data);
	void GOSTHashStage_3(TGOSTHashContext* ctx);

	void GOSTHashX(const uint8_t* a, const uint8_t* b, uint8_t* c);
	void GOSTHashS(uint8_t* state);
	void GOSTHashP(uint8_t* state);
	void GOSTHashL(uint8_t* state);
	void GOSTHashE(uint8_t* k, const uint8_t* m, uint8_t* state);
	void GOSTHashG(uint8_t* h, uint8_t* n, const uint8_t* m);
	void GOSTHashPadding(TGOSTHashContext* ctx);


	static const unsigned char Pi[256];
	static const unsigned char Tau[64];
	static const unsigned long long A[64];
	static const unsigned char C[12][64];
};


