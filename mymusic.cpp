#include "mymusic.h"
#include "ui_mymusic.h"
#include<QDebug>
myMusic::myMusic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myMusic)
{
    ui->setupUi(this);
    initUI();
    readFile();
    this->setWindowIcon(QIcon(":/picture/logo.webp"));
}

myMusic::~myMusic()
{
    delete ui;
}
//读取文件
void myMusic::readFile(){
    //设置要遍历的目录
    str_pathmusic="D:/music_download";
    QDir dir(str_pathmusic);
    //设置文件过滤器
    QStringList nameFileters;
    //设置文件过滤器的格式
    nameFileters<<"*.mp3";
    //将过滤后的文件名称存入list中
    QStringList files =dir.entryList(nameFileters,QDir::Files|QDir::Readable,QDir::Name);
    //添加到listWidget到item中
    ui->listWidget->addItems(files);
    //把item加入到listwidget中
    ui->listWidget->sortItems();
    //为列表添加默认指向
    p_item=ui->listWidget->item(0);
    p_item->setSelected(true);
//    //播放一首歌曲
//    QMediaPlayer * player =new QMediaPlayer();
//    player->setMedia(QUrl::fromLocalFile("D:/music_download"));
//    player->setVolume(80);
//    player->play();


}
void myMusic::slot_musicListRowNum(int n_number)
{
    qDebug()<<n_number<<endl;
    qDebug()<<ui->listWidget->item(n_number)->text()<<endl;
    str_music=ui->listWidget->item(n_number)->text();
    p_player=new QMediaPlayer;
    p_player->setMedia(QUrl::fromLocalFile(str_pathmusic+'/'+str_music));
    p_player->setVolume(60);
    p_player->stop();
    n_music_number=n_number;
}

//初始化界面
void myMusic::initUI(){
    connect(ui->upperbtn,SIGNAL(clicked(bool)),this,SLOT(slot_upperbtn_clicked()));
    connect(ui->playbtn,SIGNAL(clicked(bool)),this,SLOT(slot_playbtn_clicked()));
    connect(ui->downbtn,SIGNAL(clicked(bool)),this,SLOT(slot_downbtn_clicked()));
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(slot_musicListRowNum(int)));
}

void myMusic::paintEvent(QPaintEvent *){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}

void myMusic::slot_upperbtn_clicked()//上一曲
{
    qDebug()<<"上一曲";
    p_player->stop();
    if(n_music_number==0)
    {
        int nMax=ui->listWidget->count();
        str_music=ui->listWidget->item(nMax-1)->text();
        p_item=ui->listWidget->item(nMax-1);
        p_item->setSelected(true);
        QString str=str_pathmusic+'/'+str_music;
        p_player->setMedia(QUrl::fromLocalFile(str));
        p_player->setVolume(60);
        p_player->play();
        n_music_number=nMax-1;
    }
    str_music=ui->listWidget->item(n_music_number-1)->text();
    p_item=ui->listWidget->item(n_music_number-1);
    p_item->setSelected(true);

    QString str=str_pathmusic+'/'+str_music;
    p_player->setMedia(QUrl::fromLocalFile(str));
    p_player->setVolume(60);
    p_player->play();
    n_music_number=n_music_number-1;

}

void myMusic::slot_playbtn_clicked()//播放
{

    if(b_play_music)
    {
        ui->playbtn->setStyleSheet("QPushButton#playbtn{border-image: url(:/picture/stop.png);}");
        b_play_music=false;
        p_player->pause();//暂停
        qDebug()<<"暂停";
    }
    else
    {
        ui->playbtn->setStyleSheet("QPushButton#playbtn{border-image: url(:/picture/begin.png);}");
        b_play_music=true;
        p_player->play();//播放
        qDebug()<<"播放";
    }

}

void myMusic::slot_downbtn_clicked()//下一曲
{
    qDebug()<<"下一曲";
    int nMax=ui->listWidget->count();
    p_player->stop();
    if(n_music_number==nMax-1)
    {
        str_music=ui->listWidget->item(0)->text();
        p_item=ui->listWidget->item(0);
        p_item->setSelected(true);
        QString str=str_pathmusic+'/'+str_music;
        p_player->setMedia(QUrl::fromLocalFile(str));
        p_player->setVolume(60);
        p_player->play();
        n_music_number=-1;
    }
    str_music=ui->listWidget->item(n_music_number+1)->text();
    p_item=ui->listWidget->item(n_music_number+1);
    p_item->setSelected(true);

    QString str=str_pathmusic+'/'+str_music;
    p_player->setMedia(QUrl::fromLocalFile(str));
    p_player->setVolume(60);
    p_player->play();
    n_music_number=n_music_number+1;

}











