
-- New user sam (to be created by root)

CREATE USER 'sam'@'localhost' IDENTIFIED BY 'sam';

GRANT SELECT, INSERT, UPDATE, DELETE, DROP, ALTER, CREATE on SAM_BACKBONE.* TO sam@localhost;
