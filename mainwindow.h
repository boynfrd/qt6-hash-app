#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QString>

class SHA1Hasher;
class SHA256Hasher;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadFileSHA1();
    void calculateSHA1();

    void loadFileSHA256();
    void calculateSHA256();

private:
    void setupUI();

    // UI Elements for SHA-1
    QTextEdit *sha1Input;
    QLineEdit *sha1Result;
    QLabel *sha1FileLabel;
    QRadioButton *sha1NormalRadio;
    QRadioButton *sha1SaltRadio;

    // UI Elements for SHA-256
    QTextEdit *sha256Input;
    QLineEdit *sha256Result;
    QLabel *sha256FileLabel;
    QRadioButton *sha256NormalRadio;
    QRadioButton *sha256SaltRadio;

    SHA1Hasher *sha1Engine;
    SHA256Hasher *sha256Engine;
};

#endif // MAINWINDOW_H
