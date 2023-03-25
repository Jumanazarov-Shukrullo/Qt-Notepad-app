#ifndef FEEDBACKDIALOG_H
#define FEEDBACKDIALOG_H
#include <QtWidgets>

class FeedbackDialog : public QDialog
{
public:
    FeedbackDialog(QWidget* parent = nullptr);
private:
    QTextEdit *feedbackEdit;
private slots:
    void sendFeedback();
};

#endif // FEEDBACKDIALOG_H
