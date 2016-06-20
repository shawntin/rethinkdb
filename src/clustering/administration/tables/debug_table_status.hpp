// Copyright 2010-2014 RethinkDB, all rights reserved.
#ifndef CLUSTERING_ADMINISTRATION_TABLES_DEBUG_TABLE_STATUS_HPP_
#define CLUSTERING_ADMINISTRATION_TABLES_DEBUG_TABLE_STATUS_HPP_

#include <string>

#include "errors.hpp"
#include <boost/shared_ptr.hpp>

#include "clustering/administration/tables/table_common.hpp"

class server_config_client_t;

class debug_table_status_artificial_table_backend_t :
    public common_table_artificial_table_backend_t
{
public:
    debug_table_status_artificial_table_backend_t(
            name_resolver_t const &name_resolver,
            boost::shared_ptr<semilattice_readwrite_view_t<
                cluster_semilattice_metadata_t> > _semilattice_view,
            table_meta_client_t *_table_meta_client);
    ~debug_table_status_artificial_table_backend_t();

    bool write_row(
            auth::user_context_t const &user_context,
            ql::datum_t primary_key,
            bool pkey_was_autogenerated,
            ql::datum_t *new_value_inout,
            signal_t *interruptor_on_caller,
            admin_err_t *error_out);

private:
    void format_row(
            const namespace_id_t &table_id,
            const table_config_and_shards_t &config,
            const ql::datum_t &db_name_or_uuid,
            signal_t *interruptor_on_home,
            ql::datum_t *row_out)
            THROWS_ONLY(interrupted_exc_t, no_such_table_exc_t, failed_table_op_exc_t);
};

#endif /* CLUSTERING_ADMINISTRATION_TABLES_DEBUG_TABLE_STATUS_HPP_ */

