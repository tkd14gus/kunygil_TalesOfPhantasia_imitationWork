#include "stdafx.h"
#include "bullet.h"

//=============================================================
//	## bullet ## (�����Ѿ� - ������� ������ ��)
//=============================================================
HRESULT bullet::init(const char * imageName, int bulletMax, float range, bool isFrameImg)
{
	//�Ѿ� �̹��� �ʱ�ȭ
	_imageName = imageName;
	//�Ѿ˰��� �� ��Ÿ� �ʱ�ȭ
	_bulletMax = bulletMax;
	_range = range;
	//�Ѿ��̹����� ������ �̹�����?
	_isFrameImg = isFrameImg;

	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	this->move();
}

void bullet::render()
{
	if (_isFrameImg)//������ �̹���
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			_vBullet[i].bulletImage->frameRender(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
		}
	}
	else//�Ϲ� �̹���
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
		}
	}
}

void bullet::fire(float x, float y, float angle, float speed)
{
	//�Ѿ� ���Ϳ� ��°��� �����Ѵ�
	if (_bulletMax < _vBullet.size() + 1) return;

	//�Ѿ� ����ü ����
	tagBullet bullet;
	//�Ѿ˱���ü �ʱ�ȭ
	//���θ޸�, ���
	//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = 5.0f;
	bullet.angle = angle;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	if (_isFrameImg)
	{
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getFrameWidth(),
			bullet.bulletImage->getFrameHeight());
	}
	else
	{
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getWidth(),
			bullet.bulletImage->getHeight());
	}

	//���Ϳ� ���
	_vBullet.push_back(bullet);
}

void bullet::move()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
		_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed;

		if (_isFrameImg)
		{
			_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].bulletImage->getFrameWidth(),
				_vBullet[i].bulletImage->getFrameHeight());
		}
		else
		{
			_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].bulletImage->getWidth(),
				_vBullet[i].bulletImage->getHeight());
		}

		//�Ѿ��� ��Ÿ� ���� Ŀ������
		float distance = getDistance(_vBullet[i].fireX, _vBullet[i].fireY,
			_vBullet[i].x, _vBullet[i].y);
		if (_range < distance)
		{
			_vBullet.erase(_vBullet.begin() + i);
		}

	}
}
//��ź ����
void bullet::removeBullet(int index)
{
	_vBullet.erase(_vBullet.begin() + index);
}

//=============================================================
//	## missile ## (missile[0] -> �迭ó�� �̸� �����صΰ� �Ѿ˹߻�)
//=============================================================
HRESULT missile::init(int bulletMax, float range)
{
	//�Ѿ� ��Ÿ� �� �Ѿ� ���� �ʱ�ȭ
	_range = range;
	_bulletMax = bulletMax;

	//�Ѿ��� ������ŭ ����ü�� �ʱ�ȭ �� �� ���Ϳ� ���
	for (int i = 0; i < bulletMax; i++)
	{
		//�Ѿ� ����ü ����
		tagBullet bullet;
		//�Ѿ˱���ü �ʱ�ȭ
		//���θ޸�, ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("Images/missile.bmp", 26, 124, true, RGB(255, 0, 255));
		bullet.speed = 5.0f;
		bullet.fire = false;

		//���Ϳ� ���
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missile::release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].bulletImage->release();
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}

void missile::update()
{
	this->move();
}

void missile::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
	}
}

void missile::fire(float x, float y)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());
		break;
	}
}

void missile::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());
		
		//�Ѿ��� ��Ÿ����� Ŀ������
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		if (_range < distance)
		{
			_viBullet->fire = false;
		}
	}
}

//=============================================================
//	## bomb ## (��źó�� �ѹ߾� �߻��ϰ� �����ϰ� �ڵ�����)
//=============================================================
HRESULT bomb::init(int bulletMax, float range)
{
	//�Ѿ˰���, ��Ÿ� �ʱ�ȭ
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bomb::release()
{
}

void bomb::update()
{
	this->move();
}

void bomb::render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
		
		_viBullet->count++;
		if (_viBullet->count % 3 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void bomb::fire(float x, float y)
{
	//�Ѿ� ���Ϳ� ��°��� �����Ѵ�
	if (_bulletMax < _vBullet.size() + 1) return;

	//�Ѿ� ����ü ����
	tagBullet bullet;
	//�Ѿ˱���ü �ʱ�ȭ
	//���θ޸�, ���
	//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->init("Images/missile1.bmp", 416, 64, 13, 1);
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());

	//���Ϳ� ���
	_vBullet.push_back(bullet);
}

void bomb::move()
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());
	
		//��ź�� ��Ÿ����� Ŀ������
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y);
		if (_range < distance)
		{
			_viBullet->bulletImage->release();
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}
//��ź ����
void bomb::removeBomb(int index)
{
	_vBullet.erase(_vBullet.begin() + index);
}