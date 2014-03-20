#ifndef  _STATS_H_
#define  _STATS_H_

class Stats
{
public:
	Stats(void);
	~Stats(void);
	void Update(float elapsedTime);
	void Render();
private:
	ID3DXFont* m_font;
	float m_FPS;
};

#endif //_STATS_H_
