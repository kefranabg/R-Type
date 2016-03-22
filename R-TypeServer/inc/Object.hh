#ifndef					OBJECT_HH_
# define				OBJECT_HH_

class					Object
{
protected:
	int					posX;
	int					posY;
	int					posOnCaseX;
	int					posOnCaseY;
	int					sizeX;
	int					sizeY;
public:
	Object();
	~Object();
	int					getPosX() const;
	int					getPosY() const;
	int					getPosOnCaseX() const;
	int					getPosOnCaseY() const;
	int					getSizeX() const;
	int					getSizeY() const;
	void				setPosX(int);
	void				setPosY(int);
	void				setPosOnCaseX(int);
	void				setPosOnCaseY(int);
	void				setSizeX(int);
	void				setSizeY(int);
	bool				checkCollision(const Object *) const;
};

#endif