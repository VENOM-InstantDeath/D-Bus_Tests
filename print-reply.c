#include <stdio.h>
#include <dbus/dbus.h>

/* Ejemplo de programa en el cual se ejecuta el método
 * de un servicio, en este caso bluez, y luego se
 * imprime la respuesta de la operación. */

int main() {
	DBusConnection *conn = dbus_bus_get(DBUS_BUS_SYSTEM, NULL);
	DBusMessage *msg = dbus_message_new_method_call(
			"org.bluez",
			"/org/bluez/hci0",
			"org.freedesktop.DBus.Introspectable",
			"Introspect"
			);
	DBusPendingCall *pen;
	dbus_connection_send_with_reply(conn, msg, &pen, -1);
	dbus_connection_flush(conn);
	dbus_pending_call_block(pen);
	DBusMessage *reply = dbus_pending_call_steal_reply(pen);
	DBusMessageIter *iter;
	dbus_message_iter_init(reply, iter);
	char *str = NULL;
	dbus_message_iter_get_basic(iter, &str);
	puts("Finished test!");
	return 0;
}
