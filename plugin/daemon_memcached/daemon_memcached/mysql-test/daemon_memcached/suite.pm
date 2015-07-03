package My::Suite::Memcached;
use File::Basename;

@ISA = qw(My::Suite);

$ENV{DAEMON_MEMCACHED_OPT}="--plugin_dir=$::plugindir";
$ENV{INNODB_ENGINE_DIR}=$::plugindir;

bless { };

