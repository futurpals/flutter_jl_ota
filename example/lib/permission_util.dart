import 'package:flutter/foundation.dart';
import 'package:permission_handler/permission_handler.dart';

typedef PermissionUtilOnAllowedCB = void Function(bool isAllow);

class PermissionUtil {
  static void preRequestPermissions(
    List<Permission> permissions, {
    required PermissionUtilOnAllowedCB onAllowed,
  }) async {
    if (await _checkAllPermissionsStatus(permissions)) {
      onAllowed(true);
    } else {
      newRequestPermissions(permissions, onAllowed);
    }
  }

  // Permission display names used by example logs.
  static String _getPermissionName(Permission permission) {
    Map<Permission, String> permissionNames = {
      Permission.bluetooth: 'Bluetooth',
      Permission.location: 'Location',
      Permission.locationAlways: 'Always-on location',
      Permission.microphone: 'Microphone',
      Permission.storage: 'Storage',
      Permission.mediaLibrary: 'Media library',
    };
    return permissionNames[permission] ?? 'Unknown permission';
  }

  static Future<bool> _checkAllPermissionsStatus(
    List<Permission> permissions,
  ) async {
    bool status = true;
    for (var permission in permissions) {
      var permissionStatus = await permission.status;
      if (!permissionStatus.isGranted) {
        status = false;
        break;
      }
    }
    return status;
  }

  static Future newRequestPermissions(
    List<Permission> permissions,
    PermissionUtilOnAllowedCB onAllowed,
  ) async {
    var statuses = await permissions.request();
    bool allPermissionsGranted = statuses.values.every(
      (status) => status.isGranted,
    );

    // Notify the caller with the permission request result.
    onAllowed(allPermissionsGranted);

    if (allPermissionsGranted) {
      debugPrint(
        'Granted permissions: ${permissions.map(_getPermissionName)}.',
      );
    } else {
      debugPrint(
        'Denied permissions: ${statuses.entries.where((entry) => !entry.value.isGranted).map((entry) => _getPermissionName(entry.key)).toList()}.',
      );
    }
  }

  static Future _requestPermissions(
    List<Permission> permissions,
    PermissionUtilOnAllowedCB onAllowed,
  ) async {
    List<Future> requests = [];
    for (var permission in permissions) {
      if (await permission.status.isDenied) {
        // await permission.request();
        requests.add(permission.request());
      }
    }

    // Wait until every permission request completes.
    await Future.wait(requests);
    if (await _checkAllPermissionsStatus(permissions)) {
      onAllowed(true);
      debugPrint('Granted permissions: $permissions.');
    } else {
      onAllowed(false);
      debugPrint('Denied permissions: $permissions.');
    }
  }

  /// Requests permissions and returns the aggregate result through [onAllowed].
  static Future snRequestPermissions(
    List<Permission> permissions,
    PermissionUtilOnAllowedCB onAllowed,
  ) async {
    _requestPermissions(permissions, onAllowed);
  }
}
