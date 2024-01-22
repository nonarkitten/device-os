#include "application.h"
#include "unit-test/unit-test.h"

PRODUCT_VERSION(1)

#if Wiring_Ledger

namespace {

auto DEVICE_TO_CLOUD_LEDGER = "test-device-to-cloud";
auto CLOUD_TO_DEVICE_LEDGER = "test-cloud-to-device";

#ifdef DEBUG_BUILD

const Serial1LogHandler logHandler(115200, LOG_LEVEL_WARN, {
    { "system.ledger", LOG_LEVEL_ALL },
    { "wiring", LOG_LEVEL_ALL },
    { "app", LOG_LEVEL_ALL }
});

#endif // defined(DEBUG_BUILD)

bool g_ledgerSynced = false;

} // namespace

test(01_init_ledgers) {
    // Remove local ledger data
    assertEqual(Ledger::removeAll(), 0);

    auto ledger1 = Particle.ledger(DEVICE_TO_CLOUD_LEDGER);
    assertTrue(ledger1.scope() == LedgerScope::UNKNOWN);
    assertTrue(ledger1.isWritable());

    auto ledger2 = Particle.ledger(CLOUD_TO_DEVICE_LEDGER);
    assertTrue(ledger2.scope() == LedgerScope::UNKNOWN);
    assertTrue(ledger2.isWritable()); // Actual sync direction is unknown initially so the ledger is writable

    Particle.connect();
    waitUntil(Particle.connected);

    // Let the system request the ledger info
    delay(3000);

    assertTrue(ledger1.scope() == LedgerScope::DEVICE);
    assertTrue(ledger1.isWritable());

    assertTrue(ledger2.scope() == LedgerScope::DEVICE);
    assertFalse(ledger2.isWritable()); // Ledger is no longer writable
}

test(02_sync_device_to_cloud) {
    g_ledgerSynced = false;
    auto ledger = Particle.ledger(DEVICE_TO_CLOUD_LEDGER);
    ledger.onSync([](Ledger /* ledger */) {
        g_ledgerSynced = true;
    });
    LedgerData d = { { "a", 1 }, { "b", 2 }, { "c", 3 } };
    ledger.set(d);
    waitFor([]() {
        return g_ledgerSynced;
    }, 10000);
    ledger.onSync(nullptr);
    assertTrue(g_ledgerSynced);
}

test(03_update_cloud_to_device) {
    g_ledgerSynced = false;
    auto ledger = Particle.ledger(CLOUD_TO_DEVICE_LEDGER);
    ledger.onSync([](Ledger /* ledger */) {
        g_ledgerSynced = true;
    });
}

test(04_validate_cloud_to_device_sync) {
    waitFor([]() {
        return g_ledgerSynced;
    }, 10000);
    auto ledger = Particle.ledger(CLOUD_TO_DEVICE_LEDGER);
    ledger.onSync(nullptr);
    assertTrue(g_ledgerSynced);
    auto d = ledger.get();
    assertTrue((d == LedgerData{ { "d", 4 }, { "e", 5 }, { "f", 6 } }));
}

#endif // Wiring_Ledger
