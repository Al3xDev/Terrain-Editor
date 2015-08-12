/*

Author: Stoica Alexandru ( Al3xDev )
Contact al3xdev@gmail.com
License: GPL v2.0, see LICENSE file

*/


#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Terrain Editor"));

}
Widget::~Widget()
{
    delete ui;
}
void Widget::Create()
{
    std::cerr<<"Create()\n";
    ui->Ray->setMaximum(ui->MyGLWidget->terrain.max_ray);
    ui->MyGLWidget->terrain.positive_strength=true;
    bool ok;
    QString terrain_spec=QInputDialog::getText(this,tr("Creating terrain..."),tr("Lenght(X) Width(Z) Distance_Unit:"),QLineEdit::Normal,"",&ok);
    std::string std_terrain_spec=terrain_spec.toStdString();
    std::string spec[3];
    uint8_t pos;
    for(pos=0;pos<std_terrain_spec.size() && std_terrain_spec[pos]!=' ';++pos);
    std_terrain_spec[pos]=NULL;
    spec[0]=&std_terrain_spec[0];
    char *pos_=&std_terrain_spec[pos+1];
    pos++;
    for(;pos<std_terrain_spec.size() && std_terrain_spec[pos]!=' ';++pos);
    std_terrain_spec[pos]=NULL;
    spec[1]=pos_;
    ++pos;
    spec[2]=&std_terrain_spec[pos];
    uint16_t vertex_on_x,vertex_on_z;
    float distance_unit;
    bool nr=true;
    for(pos=0;pos<spec[0].size();++pos)
    {
        if(spec[0][pos]<'0' && spec[0][pos]>'9')
        {
            nr=false;
            break;
        }
    }
    if(nr)
    {
        vertex_on_x=std::atoi(&spec[0][0]);
        if(vertex_on_x<2)
        {
            QMessageBox messageBox;
            messageBox.setText("Error: Lenght terrain");
            messageBox.exec();
            return;
        }
    }
    nr=true;
    for(pos=0;pos<spec[1].size();++pos)
    {
        if(spec[1][pos]<'0' && spec[1][pos]>'9')
        {
            nr=false;
            break;
        }
    }
    if(nr)
    {
        vertex_on_z=std::atoi(&spec[1][0]);
        if(vertex_on_z<2)
        {
            QMessageBox messageBox;
            messageBox.setText("Error: Lenght terrain");
            messageBox.exec();
            return;
        }
    }
    nr=true;
    for(pos=0;pos<spec[2].size();++pos)
    {
        if(spec[2][pos]<'0' && spec[2][pos]>'9' && spec[2][pos]!='.' )
        {
            nr=false;
            break;
        }

    }
    if(nr)
    {
        for(uint8_t _pos=0;_pos<spec[2].size();++_pos)
        {
            if(spec[2][_pos]=='.')
            {
                spec[2][_pos]=',';
                break;
            }
        }
        distance_unit=std::atof(&spec[2][0]);
        if(distance_unit<=0)
        {
            QMessageBox messageBox;
            messageBox.setText("Error: Distance unit");
            messageBox.exec();
            return;
        }
    }
    this->setWindowTitle(tr("Terrain Editor"));
    ui->MyGLWidget->terrain.Create(vertex_on_x,vertex_on_z,distance_unit);
    ui->Ray->setMaximum(ui->MyGLWidget->terrain.max_ray);
    ui->Ray->setValue(1.0);
    ui->MyGLWidget->terrain.positive_strength=true;
}

void Widget::Load()
{
    std::cerr<<"Load()\n";
    bool ok;
    QString file_name= QInputDialog::getText(this,"Loading terrain...","File name:",QLineEdit::Normal,"",&ok);
    if(ok)
        if(file_name.size())
        {
            ui->MyGLWidget->terrain.Load(file_name.toStdString());
            this->setWindowTitle(file_name);
        }
        else
        {
            QMessageBox messageBox;
            messageBox.setText("Load: The file name is void");
            messageBox.exec();
            return;
        }
    ui->Ray->setMaximum(ui->MyGLWidget->terrain.max_ray);
    ui->Ray->setValue(1.0);
    ui->MyGLWidget->terrain.positive_strength=true;
}
void Widget::Save()
{
    std::cerr<<"Save()\n";

    bool ok;
    QString file_name= QInputDialog::getText(this,tr("Saving terrain..."),tr("File name:"),
                                             QLineEdit::Normal,"",&ok);
    if(ok)
       if(file_name.size()>0)
       {
           ui->MyGLWidget->terrain.Save(file_name.toStdString());
           this->setWindowTitle(file_name);
       }
       else
       {
           QMessageBox messageBox;
           messageBox.setText("Save: The file name is void");
           messageBox.exec();
       }
}
void Widget::Positive_Strength()
{
    std::cerr<<"+/- Strength\n";
    ui->MyGLWidget->terrain.positive_strength=!ui->MyGLWidget->terrain.positive_strength;
}
void Widget::Strength(double strength)
{
    std::cerr<<"Strength: "<<strength<<"\n";
    ui->MyGLWidget->terrain.strength=strength;
}
void Widget::Ray(double ray)
{
    std::cerr<<"Ray: "<<ray<<"\n";
    ui->MyGLWidget->terrain.ray=ray;
}

void Widget::on_pushButton_clicked()
{
    QMessageBox messageBox;
    messageBox.setText("");
    messageBox.setWindowTitle("About");
    messageBox.exec();
}
