#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "Reversi.h"
#include <vector>

#define MTFLAG  0b00000001//�܂��܂����̃^�[��
#define ACFLAG  0b00000010//�A�^�b�N�`�����X�g�p��
#define ARFLAG  0b00000100//�A�^�b�N�`�����X�󂯂鑤
#define PSFLAG  0b00001000//�p�X�t���O
#define GFFLAG  0b00010000//�Q�[���I��
#define FLAGNUM 3//������̉��ڂ��t���O��bit�� 0���琔����


#define ATTACKNUM 20//���Έȏ㕉����attack chance �̔��������𖞂�����

class Board
{
public:
	Board();
	
	void init();
	bool move(const Point& point);
	bool pass();
	bool undo();
	bool isGameOver() const;

	unsigned countDisc(Color color) const
	{
		return Discs[color];
	}
	
	Color getColor(const Point& p) const
	{
		return RawBoard[p.x][p.y];
	}
	
	const std::vector<Point>& getMovablePos() const
	{
		return MovablePos[Turns];
	}
	
	std::vector<Disc> getUpdate() const
	{
		if(UpdateLog.empty()) return std::vector<Disc>();
		else return UpdateLog.back();
	}
	
	Color getCurrentColor() const
	{
		return CurrentColor;
	}
	
	unsigned getTurns() const
	{
		return Turns;
	}

	std::vector<Point> getHistory() const
	{
		std::vector<Point> history;
		
		for(unsigned i=0; i<UpdateLog.size(); i++)
		{
			std::vector<Disc> update = UpdateLog[i];
			if(update.empty()) continue; // �p�X�͔�΂�
			history.push_back(update[0]);
		}
		
		return history;
	}

	
	unsigned getLiberty(const Point& p) const
	{
		return Liberty[p.x][p.y];
	}

	
	//watanabe wrote 2017/3/30
	void Reverse_disk(const Point& p, Color color);
private:


	static const unsigned NONE        =   0;
	static const unsigned UPPER       =   1;
	static const unsigned UPPER_LEFT  =   2;
	static const unsigned LEFT        =   4;
	static const unsigned LOWER_LEFT  =   8;
	static const unsigned LOWER       =  16;
	static const unsigned LOWER_RIGHT =  32;
	static const unsigned RIGHT       =  64;
	static const unsigned UPPER_RIGHT = 128;


	Color RawBoard[BOARD_SIZE+2][BOARD_SIZE+2];

	unsigned Turns;
	Color CurrentColor;

	std::vector<std::vector<Disc> > UpdateLog;

	std::vector<Point> MovablePos[MAX_TURNS+1];
	unsigned MovableDir[MAX_TURNS+1][BOARD_SIZE+2][BOARD_SIZE+2];
	unsigned Liberty[BOARD_SIZE+2][BOARD_SIZE+2];

	ColorStorage<unsigned> Discs;

	void flipDiscs(const Point& point);
	unsigned checkMobility(const Disc& disc) const;
	void initMovable();


};



#endif