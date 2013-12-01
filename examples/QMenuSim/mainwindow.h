#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static void addLogWrapper(int type, char *string);
    static void updateDisplayWrapper(int display, uint16_t *buffer);
public slots:

private slots:
    void on_LCD_update();
    void on_viewScale_changed(const int scale);
    void shrink();
    void addLogMessage(int type, char *string);
    void on_updateCheckBox_clicked();

    void on_pushButton_esc_clicked();

    void on_pushButton_left_clicked();

    void on_pushButton_right_clicked();

    void on_pushButton_ok_clicked();

    void wheelEvent ( QWheelEvent * event );

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
