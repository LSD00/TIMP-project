CREATE EXTENSION IF NOT EXISTS pgcrypto;

INSERT INTO users (email, password_hash)
SELECT
    'testuser' || i || '@example.com',
    crypt('testpassword123', gen_salt('bf'))
FROM generate_series(1, 30) AS s(i)
ON CONFLICT (email) DO NOTHING;
