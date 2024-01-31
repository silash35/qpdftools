#include "menu.hpp"
#include "ui_menu.h"

#define MENU_ICON_SIZE 50

MenuPage::MenuPage(QWidget *parent) : QWidget(parent), ui(new Ui::MenuPage) {
  ui->setupUi(this);

  ui->tbtn_compress->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  ui->tbtn_compress->setIcon(QIcon::fromTheme("zoom-out"));
  ui->tbtn_compress->setIconSize(QSize(MENU_ICON_SIZE, MENU_ICON_SIZE));

  ui->tbtn_split->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  ui->tbtn_split->setIcon(QIcon::fromTheme("edit-cut"));
  ui->tbtn_split->setIconSize(QSize(MENU_ICON_SIZE, MENU_ICON_SIZE));

  ui->tbtn_merge->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  ui->tbtn_merge->setIcon(QIcon::fromTheme("merge"));
  ui->tbtn_merge->setIconSize(QSize(MENU_ICON_SIZE, MENU_ICON_SIZE));

  ui->tbtn_rotate->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  ui->tbtn_rotate->setIcon(QIcon::fromTheme("object-rotate-right"));
  ui->tbtn_rotate->setIconSize(QSize(MENU_ICON_SIZE, MENU_ICON_SIZE));
}

MenuPage::~MenuPage() { delete ui; }

void MenuPage::on_tbtn_compress_clicked() { emit setPage(1); }

void MenuPage::on_tbtn_split_clicked() { emit setPage(2); }

void MenuPage::on_tbtn_merge_clicked() { emit setPage(3); }

void MenuPage::on_tbtn_rotate_clicked() { emit setPage(4); }
