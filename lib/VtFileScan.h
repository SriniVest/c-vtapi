#ifndef VT_FILE_SCAN_H
#define VT_FILE_SCAN_H 1

#include <stdbool.h>

// forward declarations
struct VtFileScan;
struct VtObject;

/**
* @ingroup VtApiPage
* @defgroup VtFileScan  VtFileScan object for secanning files.
* @{
*/


struct VtFileScan* VtFileScan_new(void);

/** Get a reference counter */
void VtFileScan_get(struct VtFileScan *FileScan);


/** put a reference counter */
void VtFileScan_put(struct VtFileScan **FileScan);

/**
 * @brief Set API Key
 * 
 * @param file_scan VtFileScan object pointer
 * @param api_key  Your API key
 * @return void
 */
void VtFileScan_setApiKey(struct VtFileScan *file_scan, const char *api_key);


/**
 * @brief Set the offset for the file/search  API.
 *
 * @param file_scan Object pointer
 * @param offset Offset string returned by virustotal.
 * @return void
 */
void VtFileScan_setOffset(struct VtFileScan *file_scan, const char *offset);

int VtFileScan_scan(struct VtFileScan *file_scan, const char *file_path);

/**
 * @brief Rescan a previously submitted file or schedule a scan to be performed in the future.
 *
 * @param file_scan File scan object
 * @param hash resouce to rescan
 * @param date default to 0, as not specified. If not specified, rescan immediately.
 * 		If specifed, it will be performed at the desired date.
 *      Private API permissions are required to specify this parameter
 * @param period  default 0, as not specified.   If specified period in days file
 *		to be rescaned. Private API permissions are required to specify this parameter
 * @param repeat default 0, as not specified.  If specified, file will be rescanned
 * every PERIOD paramater days, for REPEAT times.
 * @param notify_url default NULL, as not specified.  If specified, a POST will be sent to URL.
 *  Private API permissions are required to specify this parameter
 * @param notify_changes_only if notify_url set, only notify of changes
 * @return int
 */
int VtFileScan_rescanHash(struct VtFileScan *file_scan, const char *hash,
	time_t date, int period, int repeat, const char *notify_url, bool notify_changes_only);

/**
 * @brief Delete a scheduled rescan task
 *
 * @param file_scan VtFileScan object pointer
 * @param hash  resoruce to remove
 * @return int
 */

int VtFileScan_rescanDelete(struct VtFileScan *file_scan,
 const char *hash);

int VtFileScan_report(struct VtFileScan *file_scan, const char *hash);

struct VtResponse * VtFileScan_getResponse(struct VtFileScan *file_scan);


int VtFileScan_search(struct VtFileScan *file_scan, const char *query,
	void (*cb)(const char *resource, void *data),
	void *user_data);

int VtFileScan_clusters(struct VtFileScan *file_scan, const char *cluster_date,
	void (*cb)(json_t *cluster_json, void *data),
	void *user_data);

/** @} */
#endif
