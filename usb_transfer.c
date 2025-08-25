// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/fs.h>
#include <linux/atomic.h>
#include <linux/slab.h>

struct usb_dbg_ctx {
	struct dentry *root;
	atomic64_t transfer_count;
};

static struct usb_dbg_ctx g_dbg = {
	.root = NULL,
};

static int dbgfs_stats_show(struct seq_file *s, void *unused)
{
	seq_printf(s, "transfers_total: %lld\n", (long long)atomic64_read(&g_dbg.transfer_count));
	return 0;
}

static int dbgfs_stats_open(struct inode *inode, struct file *file)
{
	return single_open(file, dbgfs_stats_show, inode->i_private);
}

static const struct file_operations dbgfs_stats_fops = {
	.owner = THIS_MODULE,
	.open = dbgfs_stats_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

void usb_dbg_transfer_inc(void)
{
	atomic64_inc(&g_dbg.transfer_count);
}
EXPORT_SYMBOL_GPL(usb_dbg_transfer_inc);

int usb_dbg_init(const char *name)
{
	if (g_dbg.root)
		return 0;

	atomic64_set(&g_dbg.transfer_count, 0);
	g_dbg.root = debugfs_create_dir(name ? name : "usb_custom", NULL);
	if (IS_ERR_OR_NULL(g_dbg.root)) {
		g_dbg.root = NULL;
		return -ENOMEM;
	}

	if (!debugfs_create_file("stats", 0444, g_dbg.root, NULL, &dbgfs_stats_fops))
		return -ENOMEM;

	return 0;
}
EXPORT_SYMBOL_GPL(usb_dbg_init);

void usb_dbg_exit(void)
{
	if (g_dbg.root)
		debugfs_remove_recursive(g_dbg.root);
	g_dbg.root = NULL;
}
EXPORT_SYMBOL_GPL(usb_dbg_exit);


