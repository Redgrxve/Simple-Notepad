#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>

class TabButtonWidget;
class TextEditWidget;

namespace Ui {
class TabWidget;
}

class TabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget(QWidget *parent = nullptr);
    ~TabWidget();

    void openFileInCurrentTab(const QString &filePath);
    void saveCurrentTab(const QString &filePath);
    int addTabWithButton(const QString& tabText = "");
    TextEditWidget* getCurrentTextEdit();
    void setCurrentTabText(const QString& text);
    QString getCurrentTabText() const;
    bool isCurrentTabUnsaved();

private:
    Ui::TabWidget *ui;

signals:
    void tabAdded(int index);
    void tabClosed(int index);
    void tabUnsaved();
    void tabMoved(int from, int to);

private slots:
    void onCloseTabClicked(TabButtonWidget* sender);
    void onTextSaved(const QString& fileName);
    void onTextUnsaved();
};

#endif // TABWIDGET_H
