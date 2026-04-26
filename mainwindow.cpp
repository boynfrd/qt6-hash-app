#include "mainwindow.h"
#include "sha1hasher.h"
#include "sha256hasher.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      sha1Engine(new SHA1Hasher),
      sha256Engine(new SHA256Hasher)
{
    setupUI();
}

MainWindow::~MainWindow()
{
    delete sha1Engine;
    delete sha256Engine;
}

void MainWindow::setupUI()
{
    QTabWidget *tabs = new QTabWidget(this);

    // SHA-1 Tab
    QWidget *sha1Tab = new QWidget(this);
    QVBoxLayout *sha1Layout = new QVBoxLayout(sha1Tab);

    sha1Input = new QTextEdit(sha1Tab);
    sha1Input->setPlaceholderText("Enter text or load a file...");
    sha1Result = new QLineEdit(sha1Tab);
    sha1Result->setReadOnly(true);

    QPushButton *loadFileSHA1Button = new QPushButton("Load File", sha1Tab);
    connect(loadFileSHA1Button, &QPushButton::clicked, this, &MainWindow::loadFileSHA1);
    QPushButton *calculateSHA1Button = new QPushButton("Calculate", sha1Tab);
    connect(calculateSHA1Button, &QPushButton::clicked, this, &MainWindow::calculateSHA1);
    sha1FileLabel = new QLabel("No file loaded.", sha1Tab);

    sha1NormalRadio = new QRadioButton("Normal", sha1Tab);
    sha1SaltRadio = new QRadioButton("With Salt", sha1Tab);
    sha1NormalRadio->setChecked(true);

    sha1Layout->addWidget(sha1Input);
    sha1Layout->addWidget(loadFileSHA1Button);
    sha1Layout->addWidget(sha1FileLabel);
    sha1Layout->addWidget(sha1NormalRadio);
    sha1Layout->addWidget(sha1SaltRadio);
    sha1Layout->addWidget(calculateSHA1Button);
    sha1Layout->addWidget(sha1Result);

    tabs->addTab(sha1Tab, "SHA-1");

    // SHA-256 Tab
    QWidget *sha256Tab = new QWidget(this);
    QVBoxLayout *sha256Layout = new QVBoxLayout(sha256Tab);

    sha256Input = new QTextEdit(sha256Tab);
    sha256Input->setPlaceholderText("Enter text or load a file...");
    sha256Result = new QLineEdit(sha256Tab);
    sha256Result->setReadOnly(true);

    QPushButton *loadFileSHA256Button = new QPushButton("Load File", sha256Tab);
    connect(loadFileSHA256Button, &QPushButton::clicked, this, &MainWindow::loadFileSHA256);
    QPushButton *calculateSHA256Button = new QPushButton("Calculate", sha256Tab);
    connect(calculateSHA256Button, &QPushButton::clicked, this, &MainWindow::calculateSHA256);
    sha256FileLabel = new QLabel("No file loaded.", sha256Tab);

    sha256NormalRadio = new QRadioButton("Normal", sha256Tab);
    sha256SaltRadio = new QRadioButton("With Salt", sha256Tab);
    sha256NormalRadio->setChecked(true);

    sha256Layout->addWidget(sha256Input);
    sha256Layout->addWidget(loadFileSHA256Button);
    sha256Layout->addWidget(sha256FileLabel);
    sha256Layout->addWidget(sha256NormalRadio);
    sha256Layout->addWidget(sha256SaltRadio);
    sha256Layout->addWidget(calculateSHA256Button);
    sha256Layout->addWidget(sha256Result);

    tabs->addTab(sha256Tab, "SHA-256");

    setCentralWidget(tabs);
}

void MainWindow::loadFileSHA1()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", "", "All Files (*)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly)) {
            sha1Input->setText(file.readAll());
            sha1FileLabel->setText("File loaded successfully: " + filePath);
        }
    }
}

void MainWindow::calculateSHA1()
{
    QString input = sha1Input->toPlainText();
    if (sha1SaltRadio->isChecked()) {
        input = "SALT_" + input;
    }
    QString result = sha1Engine->hash(input);
    sha1Result->setText(result);
}

void MainWindow::loadFileSHA256()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", "", "All Files (*)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly)) {
            sha256Input->setText(file.readAll());
            sha256FileLabel->setText("File loaded successfully: " + filePath);
        }
    }
}

void MainWindow::calculateSHA256()
{
    QString input = sha256Input->toPlainText();
    if (sha256SaltRadio->isChecked()) {
        input = "SALT_" + input;
    }
    QString result = sha256Engine->hash(input);
    sha256Result->setText(result);
}
