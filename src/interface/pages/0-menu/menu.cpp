#include "menu.hpp"
#include "ui_menu.h"

MenuPage::MenuPage(QWidget *parent) : QWidget(parent), ui(new Ui::MenuPage) { ui->setupUi(this); }

MenuPage::~MenuPage() { delete ui; }

void MenuPage::on_btn_compress_clicked() { emit setPage(1); }

void MenuPage::on_btn_split_clicked() { emit setPage(2); }

void MenuPage::on_btn_merge_clicked() { emit setPage(3); }

void MenuPage::on_btn_rotate_clicked() { emit setPage(4); }
