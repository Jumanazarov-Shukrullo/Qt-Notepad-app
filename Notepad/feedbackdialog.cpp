#include "feedbackdialog.h"

FeedbackDialog::FeedbackDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle(tr("Send Feedback"));
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel *label = new QLabel(tr("Please enter your feedback below:"), this);
    layout->addWidget(label);
    feedbackEdit = new QTextEdit(this);
    layout->addWidget(feedbackEdit);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    layout->addLayout(buttonLayout);
    QPushButton *sendButton = new QPushButton(tr("Send"), this);
    buttonLayout->addWidget(sendButton);
    connect(sendButton, &QPushButton::clicked, this, &FeedbackDialog::sendFeedback);
    QPushButton *cancelButton = new QPushButton(tr("Cancel"), this);
    buttonLayout->addWidget(cancelButton);
    connect(cancelButton, &QPushButton::clicked, this, &FeedbackDialog::close);
}

void FeedbackDialog::sendFeedback() {
    // Get the user's feedback and send it via email
    QString feedback = feedbackEdit->toPlainText();
    QString subject = "Notepad Feedback";
    QString recipient = "shukrullo.coder@gmail.com";
    QString body = feedback;
    QString mailto = QString("mailto:%1?subject=%2&body=%3").arg(recipient, subject, body);
    QDesktopServices::openUrl(QUrl(mailto));
    close();
}
