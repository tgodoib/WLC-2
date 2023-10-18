#ifndef WCL_2_SECRETS_H
#define WCL_2_SECRETS_H

#include <pgmspace.h>

#ifndef SECRETS_HPP
#define SECRETS_HPP

// int8_t TIME_ZONE = -3;

const char MQTT_HOST[] = "";

static const char cacert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
-----END CERTIFICATE-----
)EOF";

static const char client_cert[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
)KEY";

// Copy contents from  XXXXXXXX-private.pem.key here ▼
static const char privkey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
-----END RSA PRIVATE KEY-----
)KEY";

#endif

#endif //WCL_2_SECRETS_H
