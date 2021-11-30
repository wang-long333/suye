#ifndef MYMUSIC_H
#define MYMUSIC_H

#include <QWidget>
#include<QStyleOption>
#include<QPainter>
#include<QDir>
#include<QListWidgetItem>
#include<QMediaPlayer>
namespace Ui {
class myMusic;
}

class myMusic : public QWidget
{
    Q_OBJECT

public:
    explicit myMusic(QWidget *parent = 0);
    ~myMusic();

private:
    Ui::myMusic *ui;

private:
    QString str_pathmusic;//音乐文件夹位置
    QListWidgetItem *p_item;//音乐列表
    bool b_play_music=false;//是否播放音乐
    QMediaPlayer * p_player;
    QString str_music;//播放名称
    int n_music_number;

private slots:
    void slot_upperbtn_clicked();//上一曲
    void slot_playbtn_clicked();//播放
    void slot_downbtn_clicked();//下一曲
    void slot_musicListRowNum(int);

private:
    void paintEvent(QPaintEvent *event);
    //读取文件
    void readFile();
    //初始化界面
    void initUI();
};

#endif // MYMUSIC_H
