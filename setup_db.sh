#!/bin/bash
# setup_db.sh
echo "Настраиваю базу для проекта..."
sudo -u postgres psql -c "ALTER USER postgres PASSWORD 'root';"
sudo -u postgres createdb users_db 2>/dev/null
echo "Готово! Теперь просто компилируй и запускай."
